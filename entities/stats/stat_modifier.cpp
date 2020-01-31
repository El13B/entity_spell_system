/*
Copyright (c) 2019-2020 Péter Magyar

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

#include "stat_modifier.h"

#include "stat.h"

Ref<Stat> StatModifier::get_owner() {
	return Ref<Stat>(_owner);
}
void StatModifier::set_owner(Ref<Stat> stat) {
	_owner = stat.ptr();
}

int StatModifier::get_id() {
	return _id;
}
void StatModifier::set_id(int value) {
	_id = value;
}

float StatModifier::get_base_mod() {
	return _base_mod;
}
void StatModifier::set_base_mod(float value) {
	_base_mod = value;

	if (_owner) {
		_owner->modifier_changed(Ref<StatModifier>(this));
	}
}

float StatModifier::get_bonus_mod() {
	return _bonus_mod;
}
void StatModifier::set_bonus_mod(float value) {
	_bonus_mod = value;

	if (_owner) {
		_owner->modifier_changed(Ref<StatModifier>(this));
	}
}

float StatModifier::get_percent_mod() {
	return _percent_mod;
}
void StatModifier::set_percent_mod(float value) {
	_percent_mod = value;

	if (_owner) {
		_owner->modifier_changed(Ref<StatModifier>(this));
	}
}

Dictionary StatModifier::to_dict() {
	return call("_to_dict");
}
void StatModifier::from_dict(const Dictionary &dict) {
	call("_from_dict", dict);
}

Dictionary StatModifier::_to_dict() {
	Dictionary dict;

	dict["id"] = _id;
	dict["base_mod"] = _base_mod;
	dict["bonus_mod"] = _bonus_mod;
	dict["percent_mod"] = _percent_mod;

	return dict;
}
void StatModifier::_from_dict(const Dictionary &dict) {
	ERR_FAIL_COND(dict.empty());

	_id = dict.get("id", 0);
	_base_mod = dict.get("base_mod", 0);
	_bonus_mod = dict.get("bonus_mod", 0);
	_percent_mod = dict.get("percent_mod", 0);
}

StatModifier::StatModifier() {
	_id = 0;
	_base_mod = 0;
	_bonus_mod = 0;
	_percent_mod = 0;

	_owner = NULL;
}

StatModifier::StatModifier(int i, float base_mod, float bonus_mod, float percent_mod, Stat *owner) {
	_id = i;
	_base_mod = base_mod;
	_bonus_mod = bonus_mod;
	_percent_mod = percent_mod;

	_owner = owner;
}

void StatModifier::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_id"), &StatModifier::get_id);
	ClassDB::bind_method(D_METHOD("set_id", "value"), &StatModifier::set_id);
	ADD_PROPERTY(PropertyInfo(Variant::INT, "id"), "set_id", "get_id");

	ClassDB::bind_method(D_METHOD("get_base_mod"), &StatModifier::get_base_mod);
	ClassDB::bind_method(D_METHOD("set_base_mod", "value"), &StatModifier::set_base_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "base_mod"), "set_base_mod", "get_base_mod");

	ClassDB::bind_method(D_METHOD("get_bonus_mod"), &StatModifier::get_bonus_mod);
	ClassDB::bind_method(D_METHOD("set_bonus_mod", "value"), &StatModifier::set_bonus_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "bonus_mod"), "set_bonus_mod", "get_bonus_mod");

	ClassDB::bind_method(D_METHOD("get_percent_mod"), &StatModifier::get_percent_mod);
	ClassDB::bind_method(D_METHOD("set_percent_mod", "value"), &StatModifier::set_percent_mod);
	ADD_PROPERTY(PropertyInfo(Variant::REAL, "percent_mod"), "set_percent_mod", "get_percent_mod");

	//Serialization
	BIND_VMETHOD(MethodInfo("_from_dict", PropertyInfo(Variant::DICTIONARY, "dict")));
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::DICTIONARY, "dict"), "_to_dict"));

	ClassDB::bind_method(D_METHOD("from_dict", "dict"), &StatModifier::from_dict);
	ClassDB::bind_method(D_METHOD("to_dict"), &StatModifier::to_dict);

	ClassDB::bind_method(D_METHOD("_from_dict", "dict"), &StatModifier::_from_dict);
	ClassDB::bind_method(D_METHOD("_to_dict"), &StatModifier::_to_dict);
}
