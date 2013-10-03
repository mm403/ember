//
// C++ Implementation: EntityIconSlot
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

#include "EntityIconSlot.h"
#include "Widget.h"
#include "EntityIconManager.h"
#include "EntityIcon.h"
#include <CEGUI/CEGUI.h>
#include <CEGUI/WindowManager.h>

using namespace CEGUI;
namespace Ember {
namespace OgreView {

namespace Gui {

EntityIconSlot::EntityIconSlot(CEGUI::Window* container)
: EntityIconDragDropTarget(container), mContainer(container), mContainedIcon(0)
{
}

EntityIconSlot::~EntityIconSlot()
{
	removeEntityIcon();
	CEGUI::WindowManager::getSingleton().destroyWindow(mContainer);
}


bool EntityIconSlot::addEntityIcon(EntityIcon* icon)
{
	if (icon) {
		if (!mContainedIcon) {
			//Resize the icon window to fit entirely in the slot window.
			icon->getDragContainer()->setSize(this->getWindow()->getSize());
			mContainedIcon = icon;
			mContainer->addChild(icon->getDragContainer()); 
			icon->setSlot(this);
			//we have to notify the container that things have changed else it won't update itself when we add the entity without dragging (cegui bug?)
			mContainer->notifyScreenAreaChanged();
			mContainer->invalidate();
		} else {
			S_LOG_WARNING("Trying to add entity icon to slot that already has one icon contained.");
			return false;
		}
	}
	return true;
}

EntityIcon* EntityIconSlot::removeEntityIcon()
{
	if (mContainedIcon) {
		mContainer->removeChild(mContainedIcon->getDragContainer());
		EntityIcon* icon = mContainedIcon;
		mContainedIcon = 0;
		icon->setSlot(0);
		//we have to notify the container that things have changed else it won't update itself when we remove the entity without dragging (cegui bug?)		
		mContainer->notifyScreenAreaChanged();
		mContainer->invalidate();
		return icon;
	} else {
		return 0;
	}
}

EntityIcon* EntityIconSlot::getEntityIcon()
{
	return mContainedIcon;
}


void EntityIconSlot::notifyIconRemoved()
{
	removeEntityIcon();
	mContainedIcon = 0;
}

CEGUI::Window* EntityIconSlot::getWindow()
{
	return mContainer;
}

void EntityIconSlot::notifyIconDraggedOff(EntityIcon* entityIcon)
{
	EventIconDraggedOff.emit(entityIcon);
}

}

}
}
