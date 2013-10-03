//
// C++ Implementation: ColouredListItem
//
// Description: 
//
//
// Author: Erik Hjortsberg <erik.hjortsberg@gmail.com>, (C) 2007
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
// 
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.//
//
#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "ColouredListItem.h"
#include "framework/LoggingInstance.h"

namespace Ember {
namespace OgreView {

namespace Gui {

ColouredListItem::ColouredListItem(const CEGUI::String& text) : ListboxTextItem(text)
{
	setColours();
}

ColouredListItem::ColouredListItem(const CEGUI::String& text, unsigned int item_id) : ListboxTextItem(text, item_id)
{
	setColours();
}

ColouredListItem::ColouredListItem(const CEGUI::String& text, unsigned int item_id, void *item_data) : ListboxTextItem(text, item_id, item_data)
{
	setColours();
}

void ColouredListItem::setColours()
{
	setSelectionColours(CEGUI::Colour(50,50,50));
	setTextColours(CEGUI::Colour(0,0,0));
	try {
		setSelectionBrushImage("EmberLook/MultiListSelectionBrush");
	} catch (...) {
		S_LOG_WARNING("Could not set selection brush image.");
	}
}

CEGUI::Sizef ColouredListItem::getPixelSize() const
{
	if (isDisabled()) {
		return CEGUI::Sizef(0, 0);
	}
	return CEGUI::ListboxTextItem::getPixelSize();
}

void ColouredListItem::draw(CEGUI::GeometryBuffer& buffer, const CEGUI::Rectf& targetRect, float alpha, const CEGUI::Rectf* clipper) const
{
	if (isDisabled()) {
		return;
	}
	CEGUI::ListboxTextItem::draw(buffer, targetRect, alpha, clipper);

}

CEGUI::ListboxItem* ColouredListItem::createColouredListItem(const CEGUI::String& text)
{
	return new ColouredListItem(text);
}

CEGUI::ListboxItem* ColouredListItem::createColouredListItem(const CEGUI::String& text, unsigned int item_id)
{
	return new ColouredListItem(text, item_id);
}

CEGUI::ListboxItem* ColouredListItem::createColouredListItem(const CEGUI::String& text, unsigned int item_id, void *item_data)
{
	return new ColouredListItem(text, item_id, item_data);
}








ColouredTreeItem::ColouredTreeItem(const CEGUI::String& text)
: TreeItem(text)
{
	setColours();
}

ColouredTreeItem::ColouredTreeItem(const CEGUI::String& text, unsigned int item_id)
: TreeItem(text, item_id)
{
	setColours();
}

ColouredTreeItem::ColouredTreeItem(const CEGUI::String& text, unsigned int item_id, void *item_data)
: TreeItem(text, item_id, item_data)
{
	setColours();
}



void ColouredTreeItem::setColours()
{
	setSelectionColours(CEGUI::Colour(50,50,50));
	setTextColours(CEGUI::Colour(0,0,0));
	try {
		setSelectionBrushImage("EmberLook/MultiListSelectionBrush");
	} catch (...) {
		S_LOG_WARNING("Could not set selection brush image.");
	}

}


CEGUI::TreeItem* ColouredTreeItem::create(const CEGUI::String& text)
{
	return new ColouredTreeItem(text);
}

CEGUI::TreeItem* ColouredTreeItem::create(const CEGUI::String& text, unsigned int item_id)
{
	return new ColouredTreeItem(text, item_id);
}

CEGUI::TreeItem* ColouredTreeItem::create(const CEGUI::String& text, unsigned int item_id, void *item_data)
{
	return new ColouredTreeItem(text, item_id, item_data);
}

}

}
}
