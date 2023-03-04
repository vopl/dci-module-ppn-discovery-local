/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#include "pch.hpp"
#include "lanScope.hpp"

namespace dci::module::ppn::discovery::local::datagramBased
{
    namespace
    {
        const net::Endpoint g_masterPoint{net::Ip4Endpoint{{}, 49073}};
        const net::Endpoint g_slavePoint{net::Ip4Endpoint{{}, 0}};
        const net::Endpoint g_broadcastPoint{net::Ip4Endpoint{{255,255,255,255}, 49073}};
        //const net::Endpoint g_broadcastPoint{net::Ip4Endpoint{{192,168,0,255}, 49073}};
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    LanScope::LanScope(host::Manager* hostManager)
        : Base(hostManager)
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    LanScope::~LanScope()
    {
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    const std::string_view& LanScope::tag()
    {
        static const std::string_view res = "LanScope";
        return res;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    const net::Endpoint& LanScope::masterPoint() const
    {
        return g_masterPoint;
    }

    const net::Endpoint& LanScope::slavePoint() const
    {
        return g_slavePoint;
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    void LanScope::tick()
    {
        dbgAssert(net());

        Bytes msg = makeMessage();
        LLOGI((isMaster()?"master":"slave")<<" sent "<<msg.size()<<" bytes");

        net()->send(std::move(msg), g_broadcastPoint);
    }

    /////////0/////////1/////////2/////////3/////////4/////////5/////////6/////////7
    bool LanScope::addressAllowed(const transport::Address& a)
    {
        using namespace std::literals;

        std::string_view scheme = utils::net::url::scheme(a.value);
        if("inproc"sv == scheme)
        {
            return false;
        }
        if("local"sv == scheme)
        {
            return false;
        }

        std::string_view authority = utils::net::url::authority(a.value);
        return utils::net::ip::isCover(utils::net::ip::Scope::lan, utils::net::ip::scope(authority));
    }
}
