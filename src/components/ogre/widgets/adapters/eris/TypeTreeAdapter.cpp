/*
 Copyright (C) 2009 Erik Hjortsberg

 This program is free software; you can redistribute it and/or modify
 it under the terms of the GNU General Public License as published by
 the Free Software Foundation; either version 2 of the License, or
 (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include "TypeTreeAdapter.h"

#include "../../ColouredListItem.h"
#include "framework/LoggingInstance.h"

#include <Eris/TypeService.h>
#include <Eris/TypeInfo.h>

#include <CEGUI/widgets/Tree.h>
#include <CEGUI/widgets/TreeItem.h>

namespace Ember
{
namespace OgreView
{

namespace Gui
{

namespace Adapters
{

namespace Eris
{

TypeTreeAdapter::TypeTreeAdapter(::Eris::TypeService& typeService, CEGUI::Tree& treeWidget) :
	mTypeService(typeService), mTreeWidget(treeWidget), mRootTypeInfo(0)
{

}

TypeTreeAdapter::~TypeTreeAdapter()
{
}

bool TypeTreeAdapter::initialize(const std::string& rootTypeName)
{
	mRootTypeInfo = mTypeService.getTypeByName(rootTypeName);
	if (mRootTypeInfo) {
		loadAllTypes();
		mTypeService.BoundType.connect(sigc::mem_fun(*this, &TypeTreeAdapter::boundAType));
		return true;
	}
	return false;
}

void TypeTreeAdapter::loadAllTypes()
{
	if (mRootTypeInfo) {
		if (mRootTypeInfo->hasUnresolvedChildren()) {
			mRootTypeInfo->resolveChildren();
		}
		const ::Eris::TypeInfoSet children = mRootTypeInfo->getChildren();
		::Eris::TypeInfoSet::const_iterator I = children.begin();
		::Eris::TypeInfoSet::const_iterator I_end = children.end();

		for (; I != I_end; ++I) {
			addToTree(*I, 0, true);
		}
	}
}

void TypeTreeAdapter::addToTree(::Eris::TypeInfo* typeInfo, CEGUI::TreeItem* parent, bool addRecursive)
{
	ReverseTypeTreeStore::iterator I = mTreeItemLookup.find(typeInfo);

	CEGUI::TreeItem* item = 0;
	if (I == mTreeItemLookup.end()) {
		item = ColouredTreeItem::create(typeInfo->getName());
		item->toggleIsOpen();
		if (!parent) {
			mTreeWidget.addItem(item);
		} else {
			parent->addItem(item);
		}
		mTypeLookup[item] = typeInfo;
		mTreeItemLookup[typeInfo] = item;
	} else {
		item = I->second;
	}

	if (addRecursive) {
		if (typeInfo->hasUnresolvedChildren()) {
			S_LOG_VERBOSE("Resolving children for " << typeInfo->getName());
			typeInfo->resolveChildren();
		}
		const ::Eris::TypeInfoSet children = typeInfo->getChildren();
		::Eris::TypeInfoSet::const_iterator I = children.begin();
		::Eris::TypeInfoSet::const_iterator I_end = children.end();

		for (; I != I_end; ++I) {
			addToTree(*I, item, addRecursive);
		}
	}

}

void TypeTreeAdapter::boundAType(::Eris::TypeInfo* typeInfo)
{

	if (mRootTypeInfo && typeInfo->isA(mRootTypeInfo)) {
		CEGUI::TreeItem* parent = 0;
		if (typeInfo->getParents().size()) {
			::Eris::TypeInfo* parentType = *typeInfo->getParents().begin();
			ReverseTypeTreeStore::iterator I = mTreeItemLookup.find(parentType);
			if (I == mTreeItemLookup.end()) {
				parent = I->second;
			}
		}
		addToTree(typeInfo, parent, true);
	}
}

::Eris::TypeInfo* TypeTreeAdapter::getSelectedTypeInfo()
{
	CEGUI::TreeItem* item = mTreeWidget.getFirstSelectedItem();
	if (item) {
		TypeTreeStore::const_iterator I = mTypeLookup.find(item);
		if (I != mTypeLookup.end()) {
			return I->second;
		}
	}
	return 0;
}

}
}
}
}
}
