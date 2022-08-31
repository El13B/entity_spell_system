/*
Copyright (c) 2019-2022 Péter Magyar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef ITEM_CONTAINER_DATA_H
#define ITEM_CONTAINER_DATA_H

#include "core/version.h"

#include "core/io/resource.h"


#include "item_container_data_entry.h"

class ItemContainerData : public Resource {
	GDCLASS(ItemContainerData, Resource);

public:
	int get_num_container_datas();
	void set_num_container_datas(int value);

	Ref<ItemContainerDataEntry> get_container_data(int index);
	void set_container_data(int index, Ref<ItemContainerDataEntry> aura);

	Vector<Variant> get_container_datas();
	void set_container_datas(const Vector<Variant> &ai_actions);

	ItemContainerData();
	~ItemContainerData();

protected:
	static void _bind_methods();

private:
	Vector<Ref<ItemContainerDataEntry> > _container_datas;
};

#endif
