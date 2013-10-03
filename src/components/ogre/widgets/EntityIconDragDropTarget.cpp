//
// C++ Implementation: EntityIconDragDropTarget
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

#include "EntityIconDragDropTarget.h"
#include "EntityIcon.h"
#include "GenericIconUserData.h"
#include <CEGUI/widgets/DragContainer.h>
#include <CEGUI/Window.h>
#include <boost/any.hpp>

using namespace CEGUI;

namespace Ember {
namespace OgreView {

namespace Gui {

EntityIconDragDropTarget::EntityIconDragDropTarget(CEGUI::Window* container)
{
	mConnections.push_back(container->subscribeEvent(CEGUI::Window::EventDragDropItemEnters, CEGUI::Event::Subscriber(& EntityIconDragDropTarget::dragContainer_DragEnter, this)));
	mConnections.push_back(container->subscribeEvent(CEGUI::Window::EventDragDropItemLeaves, CEGUI::Event::Subscriber(& EntityIconDragDropTarget::dragContainer_DragLeave, this)));
	mConnections.push_back(container->subscribeEvent(CEGUI::Window::EventDragDropItemDropped, CEGUI::Event::Subscriber(& EntityIconDragDropTarget::dragContainer_DragDropped, this)));
}

EntityIconDragDropTarget::~EntityIconDragDropTarget()
{
	for (std::vector<CEGUI::Event::Connection>::iterator I = mConnections.begin(); I != mConnections.end(); ++I) {
		(*I)->disconnect();
	}
}


bool EntityIconDragDropTarget::dragContainer_DragEnter(const CEGUI::EventArgs& args)
{
	EntityIcon* entityIcon = parseIcon(args);
	if (entityIcon) {
		return handleDragEnter(args, entityIcon);
	}
	return true;
}

bool EntityIconDragDropTarget::dragContainer_DragLeave(const CEGUI::EventArgs& args)
{
	EntityIcon* entityIcon = parseIcon(args);
	if (entityIcon) {
		return handleDragLeave(args, entityIcon);
	}
	return true;
}

bool EntityIconDragDropTarget::dragContainer_DragDropped(const CEGUI::EventArgs& args)
{
	EntityIcon* entityIcon = parseIcon(args);
	if (entityIcon) {
		return handleDragDropped(args, entityIcon);
	}
	return true;
}



bool EntityIconDragDropTarget::handleDragEnter(const CEGUI::EventArgs& args, EntityIcon* icon)
{
	EventIconEntered.emit(icon);
	return true;
}
bool EntityIconDragDropTarget::handleDragLeave(const CEGUI::EventArgs& args, EntityIcon* icon)
{
	EventIconLeaves.emit(icon);
	return true;
}
bool EntityIconDragDropTarget::handleDragDropped(const CEGUI::EventArgs& args, EntityIcon* icon)
{
	EventIconDropped.emit(icon);
	return true;
}

EntityIcon* EntityIconDragDropTarget::parseIcon(const CEGUI::EventArgs& args)
{
	const DragDropEventArgs& ddea = static_cast<const DragDropEventArgs&>(args);
	DragContainer* container = ddea.dragDropItem;
	if (container) {
		const boost::any* anyData = static_cast<const boost::any*>(container->getUserData());
		if (typeid(GenericIconUserData<EntityIcon>) == anyData->type()) {
			const GenericIconUserData<EntityIcon>& mUserData = boost::any_cast<const GenericIconUserData<EntityIcon>&>(*anyData);
			return &mUserData.getIcon();
		}
	}
	return 0;
}



}

}
}
