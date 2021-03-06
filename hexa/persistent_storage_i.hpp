//---------------------------------------------------------------------------
/// \file   persistent_storage_i.hpp
/// \brief  Interface for persistently storing game data
//
// This file is part of Hexahedra.
//
// Hexahedra is free software; you can redistribute it and/or modify it
// under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation; either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.
//
// Copyright 2012-2014, nocte@hippie.nu
//---------------------------------------------------------------------------
#pragma once

#include <stdexcept>
#include <boost/thread/mutex.hpp>
#include "basic_types.hpp"
#include "compression.hpp"
#include "entity_system.hpp"

namespace hexa
{

/** Persistent storage classes could throw this exception. */
class not_in_storage_error : public std::logic_error
{
public:
    not_in_storage_error(const std::string& w)
        : std::logic_error(std::string("requested element not found, ") + w)
    {
    }
};

/** Interface for modules that can persistently store game data. */
class persistent_storage_i
{
public:
    typedef enum {
        meta = 0, area, chunk, surface, light, cnk_height, light_hr
    } data_type;

    class raii_transaction
    {
        friend class persistent_storage_i;
        persistent_storage_i& ref_;

    protected:
        raii_transaction(persistent_storage_i& ref);

    public:
        ~raii_transaction();
    };

public:
    virtual ~persistent_storage_i() {}

    /**
     * @param index
     *  0 : uint16_t database format version number
     *  1 : uint64_t age of the world
     *  2 : Component layout of the entity system
     *  3 : A copy of "setup.json"
     */
    virtual void store_meta(uint32_t index, const std::string& blob) = 0;

    virtual std::string retrieve_meta(uint32_t index) = 0;

    virtual void store(data_type type, chunk_coordinates xyz,
                       const compressed_data& data) = 0;

    virtual void store(map_coordinates xy, chunk_height data) = 0;

    virtual compressed_data retrieve(data_type, chunk_coordinates xyz) = 0;

    virtual chunk_height retrieve(map_coordinates xy) = 0;

    virtual bool is_available(data_type type, chunk_coordinates xyz) = 0;

    virtual bool is_available(map_coordinates xy) = 0;

    virtual void store(const es::storage& es) = 0;

    virtual void store(const es::storage& es, es::storage::iterator entity_id)
        = 0;

    virtual void retrieve(es::storage& es) = 0;

    virtual void retrieve(es::storage& es, es::entity entity_id) = 0;

    virtual bool is_available(es::entity entity_id) = 0;

    virtual void remove(map_coordinates xy) { }

    virtual void remove(chunk_coordinates xyz) { }

    raii_transaction transaction() { return raii_transaction(*this); }

public:
    /** This function will be called at regular intervals.
     *  If the storage needs to do some maintenance work, such as writing
     *  buffers to file, it should be implemented here. */
    virtual void cleanup() {}

public:
    boost::mutex lock;

protected:
    virtual void begin_transaction() {}
    virtual void end_transaction() {}

private:
    boost::mutex transaction_lock_;
};

} // namespace hexa
