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

#include "stat_data.h"

Ref<StatDataEntry> StatData::get_stat_data_int(int index) {
	ERR_FAIL_INDEX_V(index, Stat::STAT_ID_TOTAL_STATS, Ref<StatDataEntry>(NULL));

	return Ref<StatDataEntry>(_entries[index]);
}

void StatData::set_stat_data_int(int index, Ref<StatDataEntry> entry) {
	ERR_FAIL_INDEX(index, Stat::STAT_ID_TOTAL_STATS);

	_entries[index] = entry;
}

Ref<StatDataEntry> StatData::get_stat_data_enum(Stat::StatId stat_id) {
	ERR_FAIL_INDEX_V(stat_id, Stat::STAT_ID_TOTAL_STATS, Ref<StatDataEntry>(NULL));

	return Ref<StatDataEntry>(_entries[stat_id]);
}

void StatData::set_stat_data_enum(Stat::StatId stat_id, Ref<StatDataEntry> entry) {
	ERR_FAIL_INDEX(stat_id, Stat::STAT_ID_TOTAL_STATS);

	_entries[stat_id] = entry;
}
Ref<LevelStatData> StatData::get_level_stat_data() {
	return _level_stat_data;
}

void StatData::set_level_stat_data(Ref<LevelStatData> value) {
	_level_stat_data = value;
}

void StatData::get_stat_for_stat(Ref<Stat> stat) {
	Ref<StatDataEntry> sd = get_stat_data_enum(stat->get_id());

	ERR_FAIL_COND(sd == NULL);

	sd->get_stats_for_stat(stat);
}

StatData::StatData() {
	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
		Ref<StatDataEntry> entry(memnew(StatDataEntry()));

		entry->set_stat_id(static_cast<Stat::StatId>(i));

		_entries[i] = Ref<StatDataEntry>(entry);
	}

	get_stat_data_enum(Stat::STAT_ID_HEALTH)->set_base(100);
	get_stat_data_enum(Stat::STAT_ID_MANA)->set_base(100);
	get_stat_data_enum(Stat::STAT_ID_SPEED)->set_base(4.2);
	get_stat_data_enum(Stat::STAT_ID_GLOBAL_COOLDOWN)->set_base(1.5);
	get_stat_data_enum(Stat::STAT_ID_MELEE_CRIT)->set_base(5);
	get_stat_data_enum(Stat::STAT_ID_MELEE_CRIT_BONUS)->set_base(50);
	get_stat_data_enum(Stat::STAT_ID_SPELL_CRIT)->set_base(5);
	get_stat_data_enum(Stat::STAT_ID_SPELL_CRIT_BONUS)->set_base(50);
	get_stat_data_enum(Stat::STAT_ID_BLOCK)->set_base(10);
	get_stat_data_enum(Stat::STAT_ID_PARRY)->set_base(15);
	get_stat_data_enum(Stat::STAT_ID_MELEE_DAMAGE_REDUCTION)->set_base(15);

	get_stat_data_enum(Stat::STAT_ID_XP_RATE)->set_base(1);
}

void StatData::_bind_methods() {

	ClassDB::bind_method(D_METHOD("get_stat_data_int", "index"), &StatData::get_stat_data_int);
	ClassDB::bind_method(D_METHOD("set_stat_data_int", "index", "entry"), &StatData::set_stat_data_int);

	ClassDB::bind_method(D_METHOD("get_stat_data_enum", "index"), &StatData::get_stat_data_enum);
	ClassDB::bind_method(D_METHOD("set_stat_data_enum", "stat_id", "entry"), &StatData::set_stat_data_enum);

	ADD_GROUP("Base Stats", "base_stat");
	for (int i = 0; i < Stat::STAT_ID_TOTAL_STATS; ++i) {
		ADD_PROPERTYI(PropertyInfo(Variant::OBJECT, "base_stat_" + Stat::stat_id_name(i), PROPERTY_HINT_RESOURCE_TYPE, "StatDataEntry"), "set_stat_data_enum", "get_stat_data_enum", i);
	}

	ClassDB::bind_method(D_METHOD("get_level_stat_data"), &StatData::get_level_stat_data);
	ClassDB::bind_method(D_METHOD("set_level_stat_data", "value"), &StatData::set_level_stat_data);
	ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "level_stat_data", PROPERTY_HINT_RESOURCE_TYPE, "LevelStatData"), "set_level_stat_data", "get_level_stat_data");
}
