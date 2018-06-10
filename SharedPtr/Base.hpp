/*
 * Copyright (c) 2018 Guo Xiang
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __BASE_HPP__
#define __BASE_HPP__

#include <EasyCpp.hpp>

enum ClassIdentify {
	CI_BASEA,
	CI_BASEB,
	CI_DERIVE,
	CI_BASEA_DERIVE,
	CI_BASEB_DERIVE,
};

DEFINE_CLASS(BaseA);
DEFINE_CLASS(BaseB);
DEFINE_INTERFACE(BaseC);

class CBaseA
{
public:
	virtual ~CBaseA(void) {}
	virtual enum ClassIdentify GetBaseAType(void) const
	{
		return CI_BASEA;
	}

	inline enum ClassIdentify Identify(void) const
	{
		return CI_BASEA;
	}
};

class CBaseB :
	public CEnableSharedPtr<CBaseB>
{
public:
	virtual ~CBaseB(void) {}
	virtual enum ClassIdentify GetBaseBType(void) const
	{
		return CI_BASEB;
	}

	inline enum ClassIdentify Identify(void) const
	{
		return CI_BASEB;
	}

	inline decltype(auto) ShareTest(void)
	{
		return Share();
	}

	inline decltype(auto) ConstShareTest(void) const
	{
		return Share();
	}
};

class IBaseC
{
public:
	virtual ~IBaseC(void) {}
	virtual enum ClassIdentify GetBaseCType(void) const = 0;
};

#endif /* __BASE_HPP__ */

