/* This file is part of the the dci project. Copyright (C) 2013-2021 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#include "pch.hpp"
#include "machineScope.hpp"

namespace dci::module::ppn::discovery::local::datagramBased
{
    namespace
    {
        constexpr char g_masterPointValue[] {"\0dci-ppn-discovery-local-machineScope"};
        const net::Endpoint g_masterPoint {net::LocalEndpoint{String{g_masterPointValue, sizeof(g_masterPointValue)-1}}};
        const net::Endpoint g_slavePoint {net::LocalEndpoint{}};
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    MachineScope::MachineScope(host::Manager* hostManager)
        : Base(hostManager)
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    MachineScope::~MachineScope()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    const std::string_view& MachineScope::tag()
    {
        static const std::string_view res = "MachineScope";
        return res;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    const net::Endpoint& MachineScope::masterPoint() const
    {
        return g_masterPoint;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    const net::Endpoint& MachineScope::slavePoint() const
    {
        return g_slavePoint;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void MachineScope::tick()
    {
        dbgAssert(net());

        if(!isMaster())
        {
            Bytes msg = makeMessage();
            //LLOGI((_isMaster?"master":"slave")<<" sent "<<msg.size()<<" bytes");

            net()->send(std::move(msg), g_masterPoint);
        }
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    bool MachineScope::addressAllowed(const transport::Address& a)
    {
        using namespace std::literals;
        if("inproc"sv == utils::net::url::scheme(a.value))
        {
            return false;
        }

        return true;
    }
}
