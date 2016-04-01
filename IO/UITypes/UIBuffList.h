/////////////////////////////////////////////////////////////////////////////
// This file is part of the Journey MMORPG client                           //
// Copyright � 2015 Daniel Allendorf                                        //
//                                                                          //
// This program is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU Affero General Public License as           //
// published by the Free Software Foundation, either version 3 of the       //
// License, or (at your option) any later version.                          //
//                                                                          //
// This program is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of           //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the            //
// GNU Affero General Public License for more details.                      //
//                                                                          //
// You should have received a copy of the GNU Affero General Public License //
// along with this program.  If not, see <http://www.gnu.org/licenses/>.    //
//////////////////////////////////////////////////////////////////////////////
#pragma once
#include "Constants.h"
#include "Graphics\Texture.h"
#include "IO\Element.h"
#include "IO\Components\IconCover.h"
#include <unordered_map>

namespace IO
{
	using std::unordered_map;

	class BuffIcon
	{
	public:
		BuffIcon(int32_t buff, int32_t dur);
		BuffIcon();
		~BuffIcon();

		void draw(Point<int16_t> position, float alpha) const;
		bool update();

	private:
		using Texture = Graphics::Texture;

		static const uint16_t FLASH_TIME = 3000;

		Texture icon;
		IconCover cover;
		int32_t buffid;
		int32_t duration;
		Linear<float> opacity;
		float opcstep;
	};


	class UIBuffList : public UIElement
	{
	public:
		UIBuffList();

		void draw(float inter) const override;
		void update() override;
		Cursor::State sendmouse(bool pressed, Point<int16_t> position) override;

		void addbuff(int32_t buffid, int32_t duration);

	private:
		unordered_map<int32_t, BuffIcon> icons;
	};


	class ElementBuffList : public Element
	{
		UIElement::Type type() const override
		{
			return UIElement::BUFFLIST;
		}

		UIElement* instantiate() const override
		{
			return new UIBuffList();
		}
	};
}