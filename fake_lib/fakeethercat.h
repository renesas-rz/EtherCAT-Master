/*****************************************************************************
 *
 *  Copyright (C) 2024  Bjarne von Horn, Ingenieurgemeinschaft IgH
 *
 *  This file is part of the IgH EtherCAT master userspace library.
 *
 *  The IgH EtherCAT master userspace library is free software; you can
 *  redistribute it and/or modify it under the terms of the GNU Lesser General
 *  Public License as published by the Free Software Foundation; version 2.1
 *  of the License.
 *
 *  The IgH EtherCAT master userspace library is distributed in the hope that
 *  it will be useful, but WITHOUT ANY WARRANTY; without even the implied
 *  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public License
 *  along with the IgH EtherCAT master userspace library. If not, see
 *  <http://www.gnu.org/licenses/>.
 *
 ****************************************************************************/

#pragma once

#include <ecrt.h>
#include <rtipc.h>

#include <iostream>
#include <iomanip>
#include <list>
#include <map>
#include <memory>
#include <string>
#include <vector>

struct Offset
{
    int bytes;
    int bits;

    constexpr Offset(int bytes,
                     int bits) : bytes(bytes), bits(bits) {}

    constexpr bool operator!=(const Offset &other) const noexcept
    {
        return bytes != other.bytes || bits != other.bits;
    }
};

constexpr Offset NotFound(-1, -1);

struct pdo
{
    std::vector<ec_pdo_entry_info_t> entries;

    size_t sizeInBytes() const;

    Offset findEntry(uint16_t idx, uint8_t subindex) const;
};

struct syncManager
{
    ec_direction_t dir;
    std::map<uint16_t /* address */, pdo> pdos;
};

class ec_address
{
    uint32_t value;

public:
    ec_address(uint16_t alias, /**< Slave alias. */
               uint16_t position /**< Slave position. */)
        : value(static_cast<uint32_t>(alias) << 16 | position)
    {
    }

    uint16_t getAlias() const { return value >> 16; }
    uint16_t getPosition() const { return value & 0xFFFF; }
    uint32_t getCombined() const { return value; }

    bool operator<(const ec_address &other) const noexcept
    {
        return value < other.value;
    }

    bool operator==(const ec_address &other) const noexcept
    {
        return value == other.value;
    }
};


class sdo_address
{
    uint32_t value;

public:
    sdo_address(uint16_t index, /**< Slave alias. */
               uint8_t subindex /**< Slave position. */)
        : value(static_cast<uint32_t>(index) << 8 | subindex)
    {
    }

    uint16_t getIndex() const { return value >> 8; }
    uint8_t getSubIndex() const { return value & 0xFF; }
    uint32_t getCombined() const { return value; }

    bool operator<(const sdo_address &other) const noexcept
    {
        return value < other.value;
    }

    bool operator==(const sdo_address &other) const noexcept
    {
        return value == other.value;
    }
};

struct ec_slave_config
{
    ec_address address;
    uint32_t vendor_id;    /**< Expected vendor ID. */
    uint32_t product_code; /**< Expected product code. */
    std::map<unsigned int, syncManager> sync_managers;
    std::map<sdo_address, std::basic_string<uint8_t>> sdos;

    ec_slave_config(
        ec_address address,
        uint32_t vendor_id, /**< Expected vendor ID. */
        uint32_t product_code /**< Expected product code. */)
        : address(address), vendor_id(vendor_id), product_code(product_code)
    {
    }
};

struct ec_domain
{

private:
    struct PdoMap
    {
        size_t offset;
        size_t size_bytes;
        ec_address slave_address;
        unsigned int syncManager;
        uint16_t pdo_index;
        ec_direction_t dir;

        PdoMap(
            size_t offset,
            size_t size_bytes,
            ec_address slave_address,
            unsigned int syncManager,
            uint16_t pdo_index,
            ec_direction_t dir)
            : offset(offset), size_bytes(size_bytes), slave_address(slave_address), syncManager(syncManager), pdo_index(pdo_index), dir(dir)
        {
        }
    };

    std::vector<uint8_t> data;
    std::vector<unsigned char> connected;
    std::vector<PdoMap> mapped_pdos;
    rtipc_group *rt_group;
    const char *prefix;
    bool activated_ = false;
    size_t numSlaves = 0;

public:
    explicit ec_domain(struct rtipc *rtipc, const char *prefix);

    uint8_t *getData() const
    {
        if (!activated_)
            return nullptr;
        return const_cast<uint8_t *>(data.data());
    }

    int activate(int domain_id);
    int process();
    int queue();

    size_t getNumSlaves() const { return numSlaves; }

    ssize_t map(ec_slave_config const &config, unsigned int syncManager,
                uint16_t pdo_index);
};

struct ec_master
{
private:
    struct RtIpcDeleter
    {
        void operator()(struct rtipc *r) const
        {
            rtipc_exit(r);
        }
    };

    std::list<ec_domain> domains;
    std::map<ec_address, ec_slave_config> slaves;
    std::unique_ptr<struct rtipc, RtIpcDeleter> rt_ipc;

public:
    ec_master();

    int activate();
    ec_domain *createDomain();

    int getNoSlaves() const { return slaves.size(); }

ec_slave_config_t *slave_config(
    uint16_t alias,       /**< Slave alias. */
    uint16_t position,    /**< Slave position. */
    uint32_t vendor_id,   /**< Expected vendor ID. */
    uint32_t product_code /**< Expected product code. */
);
};
