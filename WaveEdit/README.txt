Filter design:
Filter superclass is a abstract method with virtual WaveFile* transform() = 0;
FilterEcho, FilterSpeedUp, FilterSlowdown inheritance from Filter
In FilterManager, add menu according to number of filter, in getFilter() method, return a wavefile for the wavefile processed by filter.
In WaveEditView reserve 7000-7010 for FilterManager, use COMMAND_ON_RANGE to add FilterManager Handler. FilterManager call transform according to the id.

Other Extras:
Volume Up / Volume Down in the in FilterManager

