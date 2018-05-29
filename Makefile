# Copyright (c) 2018 Guo Xiang
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, version 3.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
# General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program. If not, see <http://www.gnu.org/licenses/>.

SRC := \
  SharedPtr/SharedPtrTestConstructor.cpp \
  SharedPtr/SharedPtrTestEqual.cpp \
  SharedPtr/SharedPtrTestIsEqual.cpp \
  SharedPtr/SharedPtrTestAddEqual.cpp \
  SharedPtr/SharedPtrTestSubEqual.cpp \
  SharedPtr/SharedPtrTestCompare.cpp \
  SharedPtr/SharedPtrTestToken.cpp \
  SharedPtr/SharedPtrTestOtherOperators.cpp \
  SharedPtr/SharedPtrTestOthers.cpp \
  SharedPtr/SharedPtrTest.cpp \
  Main.cpp

include $(TEMPLATE)

#SRC := \
#  $(PKG_NAME)/Main.cpp \
#  $(PKG_NAME)/SharedPtr/SharedPtrTest.cpp \
#  $(PKG_NAME)/StringTest.cpp \
#  $(PKG_NAME)/DataStructTest.cpp
