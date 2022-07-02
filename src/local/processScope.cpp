/* This file is part of the the dci project. Copyright (C) 2013-2022 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#include "pch.hpp"
#include "processScope.hpp"

namespace dci::module::ppn::discovery::local
{
    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    ProcessScope::ProcessScope()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    ProcessScope::~ProcessScope()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void ProcessScope::started()
    {
        for(ProcessScope* other : _randezvous)
        {
            if(other != this)
            {
                other->emitEntries(this->entriesOut());
                emitEntries(other->entriesOut());
            }
        }

        _randezvous.insert(this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void ProcessScope::stopped()
    {
        _randezvous.erase(this);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void ProcessScope::declared(const Entry& entry)
    {
        for(ProcessScope* other : _randezvous)
        {
            if(other != this)
            {
                other->emitEntry(entry);
            }
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    ProcessScope::Randezvous ProcessScope::_randezvous;
}
