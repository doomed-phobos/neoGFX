// collider.hpp
/*
  neogfx C++ GUI Library
  Copyright (c) 2018 Leigh Johnston.  All Rights Reserved.
  
  This program is free software: you can redistribute it and / or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.
  
  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.
  
  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <neogfx/neogfx.hpp>
#include <neolib/uuid.hpp>
#include <neolib/string.hpp>
#include <neogfx/game/i_component_data.hpp>

namespace neogfx
{
	struct box_collider : i_component_data
	{
		vec3 origin;
		vec3 size;
		uint64_t collisionMask;
		uint32_t collisionEventId;

		struct meta
		{
			static const neolib::uuid& id()
			{
				static const neolib::uuid sId = {};
				return sId;
			}
			static const neolib::i_string& name()
			{
				static const neolib::string sName = "Box Collider";
				return sName;
			}
			static uint32_t field_count()
			{
				return 4;
			}
			static component_data_field_type field_type(uint32_t aFieldIndex)
			{
				switch (aFieldIndex)
				{
				case 0:
				case 1:
					return component_data_field_type::Vec3 | component_data_field_type::Float64;
				case 2:
					return component_data_field_type::Uint64;
				case 3:
					return component_data_field_type::Uint32 | component_data_field_type::Internal;
				}
			}
			static const neolib::i_string& field_name(uint32_t aFieldIndex)
			{
				static const neolib::string sFieldNames[] =
				{
					"Origin",
					"Size",
					"Collision Mask",
					"Collision Event Id",
				};
				return sFieldNames[aFieldIndex];
			}
		};
	};
}