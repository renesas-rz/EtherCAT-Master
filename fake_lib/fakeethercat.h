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

#include <iostream>
#include <iomanip>
#include <list>
#include <map>
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

    bool operator<(const ec_address &other) const noexcept
    {
        return value < other.value;
    }

    bool operator==(const ec_address &other) const noexcept
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

    struct PdoMap
    {
        size_t offset;
        ec_address slave_address;
        unsigned int syncManager;
        uint16_t pdo_index;

        PdoMap(
            size_t offset,
            ec_address slave_address,
            unsigned int syncManager,
            uint16_t pdo_index)
            : offset(offset), slave_address(slave_address), syncManager(syncManager), pdo_index(pdo_index)
        {
        }
    };

    std::vector<uint8_t> data;
    std::vector<PdoMap> mapped_pdos;

    void activate();

    ssize_t map(ec_slave_config const &config, unsigned int syncManager,
                uint16_t pdo_index);
};

struct ec_master
{
    std::list<ec_domain> domains;
    std::map<ec_address, ec_slave_config> slaves;
};
