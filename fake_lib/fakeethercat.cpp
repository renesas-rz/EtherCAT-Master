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

#include "fakeethercat.h"

#include <cstring>

size_t pdo::sizeInBytes() const
{
    size_t ans = 0;
    for (const auto &entry : entries)
    {
        ans += entry.bit_length;
    }
    return (ans + 7) / 8;
}

Offset pdo::findEntry(uint16_t idx, uint8_t subindex) const
{
    size_t offset_bits = 0;
    for (const auto &entry : entries)
    {
        if (entry.index == idx && entry.subindex == subindex)
        {
            return Offset(offset_bits / 8, offset_bits % 8);
        }
        offset_bits += entry.bit_length;
    }
    return NotFound;
}

void ec_domain::activate()
{
}

ssize_t ec_domain::map(ec_slave_config const &config, unsigned int syncManager,
                       uint16_t pdo_index)
{
    for (const auto &pdo : mapped_pdos)
    {
        if (pdo.slave_address == config.address && syncManager == pdo.syncManager && pdo_index == pdo.pdo_index)
        {
            // already mapped;
            return pdo.offset;
        }
    }
    const auto ans = data.size();
    mapped_pdos.emplace_back(ans, config.address, syncManager, pdo_index);
    data.resize(ans + config.sync_managers.at(syncManager).pdos.at(pdo_index).sizeInBytes());
    return ans;
}

uint8_t *ecrt_domain_data(
    const ec_domain_t *domain)
{
    return const_cast<uint8_t *>(domain->data.data());
}

int ecrt_domain_process(
    ec_domain_t *domain)
{
    if (domain->data.empty())
        return 0;
    std::cout << ' ';
    for (const auto i : domain->data)
        std::cout << std::hex << std::setw(2) << std::setfill('0') << (int)i;
    return 0;
}
int ecrt_domain_queue(
    ec_domain_t *domain)
{
    return 0;
}

int ecrt_domain_state(
    const ec_domain_t *domain, /**< Domain. */
    ec_domain_state_t *state   /**< Pointer to a state object to store the
                                 information. */
)
{
    return 0;
}

int ecrt_master_activate(
    ec_master_t *master /**< EtherCAT master. */
)
{
    for (auto &domain : master->domains)
        domain.activate();
    return 0;
}

int ecrt_master_application_time(
    ec_master_t *master, /**< EtherCAT master. */
    uint64_t app_time    /**< Application time. */
)
{
    return 0;
}

ec_domain_t *ecrt_master_create_domain(
    ec_master_t *master /**< EtherCAT master. */
)
{
    master->domains.emplace_back();
    return &master->domains.back();
}

int ecrt_master_receive(
    ec_master_t *master /**< EtherCAT master. */
)
{
    std::cout << '\r';
    return 0;
}

int ecrt_master_send(
    ec_master_t *master /**< EtherCAT master. */
)
{
    std::cout << std::flush;
    return 0;
}

ec_slave_config_t *ecrt_master_slave_config(
    ec_master_t *master,  /**< EtherCAT master */
    uint16_t alias,       /**< Slave alias. */
    uint16_t position,    /**< Slave position. */
    uint32_t vendor_id,   /**< Expected vendor ID. */
    uint32_t product_code /**< Expected product code. */
)
{
    const ec_address address{alias, position};
    const auto it = master->slaves.find(address);
    if (it != master->slaves.end())
    {
        if (it->second.vendor_id == vendor_id && it->second.product_code == product_code)
            return &it->second;
        else
        {
            std::cerr << "Attempted to reconfigure slave (" << alias << "," << position << ")!\n";
            return nullptr;
        }
    }
    else
    {
        return &master->slaves.insert(std::make_pair<ec_address, ec_slave_config>(ec_address{address}, ec_slave_config{address, vendor_id, product_code})).first->second;
    }
}
int ecrt_master_state(
    const ec_master_t *master, /**< EtherCAT master. */
    ec_master_state_t *state   /**< Structure to store the information. */
)
{
    state->slaves_responding = master->slaves.size();
    state->link_up = 1;
    state->al_states = 8;
    return 0;
}
int ecrt_master_sync_reference_clock(
    ec_master_t *master /**< EtherCAT master. */
)
{
    return 0;
}
int ecrt_master_sync_slave_clocks(
    ec_master_t *master /**< EtherCAT master. */
)
{
    return 0;
}
ec_master_t *ecrt_request_master(
    unsigned int master_index /**< Index of the master to request. */
)
{
    return new ec_master();
}

int ecrt_slave_config_complete_sdo(
    ec_slave_config_t *sc, /**< Slave configuration. */
    uint16_t index,        /**< Index of the SDO to configure. */
    const uint8_t *data,   /**< Pointer to the data. */
    size_t size            /**< Size of the \a data. */
)
{
}
ec_sdo_request_t *ecrt_slave_config_create_sdo_request(
    ec_slave_config_t *sc, /**< Slave configuration. */
    uint16_t index,        /**< SDO index. */
    uint8_t subindex,      /**< SDO subindex. */
    size_t size            /**< Data size to reserve. */
)
{
}
int ecrt_slave_config_dc(
    ec_slave_config_t *sc,    /**< Slave configuration. */
    uint16_t assign_activate, /**< AssignActivate word. */
    uint32_t sync0_cycle,     /**< SYNC0 cycle time [ns]. */
    int32_t sync0_shift,      /**< SYNC0 shift time [ns]. */
    uint32_t sync1_cycle,     /**< SYNC1 cycle time [ns]. */
    int32_t sync1_shift       /**< SYNC1 shift time [ns]. */
)
{
    return 0;
}
int ecrt_slave_config_idn(
    ec_slave_config_t *sc, /**< Slave configuration. */
    uint8_t drive_no,      /**< Drive number. */
    uint16_t idn,          /**< SoE IDN. */
    ec_al_state_t state,   /**< AL state in which to write the IDN (PREOP or
                             SAFEOP). */
    const uint8_t *data,   /**< Pointer to the data. */
    size_t size            /**< Size of the \a data. */
)
{
    return 0;
}
int ecrt_slave_config_pdos(
    ec_slave_config_t *sc,       /**< Slave configuration. */
    unsigned int n_syncs,        /**< Number of sync manager configurations in
                                   \a syncs. */
    const ec_sync_info_t syncs[] /**< Array of sync manager
                                   configurations. */
)
{
    for (unsigned int sync_idx = 0; sync_idx < n_syncs; ++sync_idx)
    {
        if (syncs[sync_idx].index == 0xff)
        {
            return 0;
        }
        auto &manager = sc->sync_managers[syncs[sync_idx].index];
        manager.dir = syncs[sync_idx].dir;
        for (unsigned int i = 0; i < syncs[sync_idx].n_pdos; ++i)
        {
            const auto &in_pdo = syncs[sync_idx].pdos[i];
            if (in_pdo.n_entries == 0 || !in_pdo.entries)
            {
                std::cerr << "Default mapping not supported.";
                return -1;
            }
            auto &out_pdo = manager.pdos[in_pdo.index];
            for (unsigned int pdo_entry_idx = 0; pdo_entry_idx < in_pdo.n_entries; ++pdo_entry_idx)
            {
                out_pdo.entries.push_back(in_pdo.entries[pdo_entry_idx]);
            }
        }
    }

    return 0;
}
int ecrt_slave_config_reg_pdo_entry(
    ec_slave_config_t *sc,     /**< Slave configuration. */
    uint16_t entry_index,      /**< Index of the PDO entry to register. */
    uint8_t entry_subindex,    /**< Subindex of the PDO entry to register. */
    ec_domain_t *domain,       /**< Domain. */
    unsigned int *bit_position /**< Optional address if bit addressing
                             is desired */
)
{
    for (auto sync_it : sc->sync_managers)
    {
        for (auto pdo_it : sync_it.second.pdos)
        {
            const auto offset = pdo_it.second.findEntry(entry_index, entry_subindex);
            if (offset != NotFound)
            {
                const auto domain_offset = domain->map(*sc, sync_it.first, pdo_it.first);
                if (domain_offset != -1)
                {
                    if (bit_position)
                        *bit_position = offset.bits;
                    return domain_offset + offset.bytes;
                }
                else
                {
                    return -1;
                }
            }
        }
    }
    return -1; // offset
}

int ecrt_slave_config_sdo(
    ec_slave_config_t *sc, /**< Slave configuration. */
    uint16_t index,        /**< Index of the SDO to configure. */
    uint8_t subindex,      /**< Subindex of the SDO to configure. */
    const uint8_t *data,   /**< Pointer to the data. */
    size_t size            /**< Size of the \a data. */
)
{
}

void ecrt_write_lreal(void *data, double const value)
{
    memcpy(data, &value, sizeof(value));
}
void ecrt_write_real(void *data, float const value)
{
    memcpy(data, &value, sizeof(value));
}
