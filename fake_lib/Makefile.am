#------------------------------------------------------------------------------
#
#  Copyright (C) 2006-2024  Florian Pose, Ingenieurgemeinschaft IgH
#
#  This file is part of the IgH EtherCAT master userspace library.
#
#  The IgH EtherCAT master userspace library is free software; you can
#  redistribute it and/or modify it under the terms of the GNU Lesser General
#  Public License as published by the Free Software Foundation; version 2.1 of
#  the License.
#
#  The IgH EtherCAT master userspace library is distributed in the hope that
#  it will be useful, but WITHOUT ANY WARRANTY; without even the implied
#  warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU Lesser General Public License for more details.
#
#  You should have received a copy of the GNU Lesser General Public License
#  along with the IgH EtherCAT master userspace library. If not, see
#  <http://www.gnu.org/licenses/>.
#
#------------------------------------------------------------------------------

lib_LTLIBRARIES = libfakeethercat.la

#------------------------------------------------------------------------------

libfakeethercat_la_SOURCES = \
	fakeethercat.cpp

noinst_HEADERS = \
	fakeethercat.h

libfakeethercat_la_CXXFLAGS = \
	-fno-strict-aliasing \
	-Wall \
	-I$(top_srcdir)/include \
	-Dethercat_EXPORTS \
	-fvisibility=hidden \
	$(RTIPC_CFLAGS)

libfakeethercat_la_LDFLAGS = -version-info 3:0:2 \
	$(RTIPC_LIBS) \
	-Wl,--version-script=$(srcdir)/../lib/libethercat.map \
	-fvisibility=hidden

libfakeethercat_la_DEPENDENCIES = ../lib/libethercat.map
