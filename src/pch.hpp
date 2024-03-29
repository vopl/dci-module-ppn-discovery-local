/* This file is part of the the dci project. Copyright (C) 2013-2023 vopl, shtoba.
   This program is free software: you can redistribute it and/or modify it under the terms of the GNU Affero General Public
   License as published by the Free Software Foundation, either version 3 of the License, or (at your option) any later version.
   This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty
   of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU Affero General Public License for more details.
   You should have received a copy of the GNU Affero General Public License along with this program. If not, see <https://www.gnu.org/licenses/>. */

#pragma once

#include <dci/host.hpp>
#include <dci/logger.hpp>
#include <dci/utils/atScopeExit.hpp>
#include <dci/poll/waitableTimer.hpp>
#include <dci/stiac.hpp>
#include <dci/utils/uri.hpp>
#include <dci/utils/ip.hpp>
#include "ppn/discovery/local.hpp"

namespace dci::module::ppn::discovery
{
    using namespace dci;

    namespace transport = idl::ppn::transport;
    namespace link      = idl::ppn::node::link;
    namespace node      = idl::ppn::node;
    namespace api       = idl::ppn::discovery::local;
    namespace net       = idl::net;
}
