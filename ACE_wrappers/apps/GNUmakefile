# -*- makefile -*-
#----------------------------------------------------------------------------
#       GNU ACE Workspace
#
# 
#
# This file was generated by MPC.  Any changes made directly to
# this file will be lost the next time it is generated.
#
# MPC Command:
# /home/johnny/DOC_ROOT/stage-6879/ACE_wrappers/bin/mwc.pl -type gnuace -exclude TAO/TAO_ACE.mwc -workers 8 -recurse -hierarchy -relative ACE_ROOT=/home/johnny/DOC_ROOT/stage-6879/ACE_wrappers -relative TAO_ROOT=/home/johnny/DOC_ROOT/stage-6879/ACE_wrappers/TAO
#
#----------------------------------------------------------------------------

MAKEFILE = GNUmakefile

ifeq ($(findstring k,$(MAKEFLAGS)),k)
  KEEP_GOING = -
endif

include $(ACE_ROOT)/include/makeinclude/macros.GNU

all: Gateway-target gatewayd Gateway_Peer gateway_peerd blobby http_client JAWS-target JAWS_server JAWS2-target HTTPU JAWS3-target JAWS3_server drwho__server drwho__client gperf_docs gperf-target cinset adainset cppinset iinset iinset2 m3inset pinset preinset taoinset tinset mkcsregdb-target soreduce-target

depend: Gateway-target-depend gatewayd-depend Gateway_Peer-depend gateway_peerd-depend blobby-depend http_client-depend JAWS-target-depend JAWS_server-depend JAWS2-target-depend HTTPU-depend JAWS3-target-depend JAWS3_server-depend drwho__server-depend drwho__client-depend gperf_docs-depend gperf-target-depend cinset-depend adainset-depend cppinset-depend iinset-depend iinset2-depend m3inset-depend pinset-depend preinset-depend taoinset-depend tinset-depend mkcsregdb-target-depend soreduce-target-depend

REMAINING_TARGETS := $(filter-out all depend,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)
.PHONY: $(REMAINING_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.Gateway $(@)
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.gatewayd $(@)
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.Gateway_Peer $(@)
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.gateway_peerd $(@)
	$(KEEP_GOING)@cd JAWS/clients/Blobby && $(MAKE) -f GNUmakefile.blobby $(@)
	$(KEEP_GOING)@cd JAWS/clients/Caching && $(MAKE) -f GNUmakefile.http_client $(@)
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS $(@)
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS_server $(@)
	$(KEEP_GOING)@cd JAWS2/JAWS && $(MAKE) -f GNUmakefile.JAWS2 $(@)
	$(KEEP_GOING)@cd JAWS2/HTTPU && $(MAKE) -f GNUmakefile.HTTPU $(@)
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3 $(@)
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3_server $(@)
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__server $(@)
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__client $(@)
	$(KEEP_GOING)@cd gperf && $(MAKE) -f GNUmakefile.gperf_docs $(@)
	$(KEEP_GOING)@cd gperf/src && $(MAKE) -f GNUmakefile.gperf $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.adainset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cppinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset2 $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.m3inset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.pinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.preinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.taoinset $(@)
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.tinset $(@)
	$(KEEP_GOING)@cd mkcsregdb && $(MAKE) -f GNUmakefile.mkcsregdb $(@)
	$(KEEP_GOING)@cd soreduce && $(MAKE) -f GNUmakefile.soreduce $(@)

.PHONY: Gateway-target
Gateway-target:
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.Gateway all

.PHONY: Gateway-target-depend
Gateway-target-depend:
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.Gateway depend

.PHONY: gatewayd
gatewayd: Gateway-target
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.gatewayd all

.PHONY: gatewayd-depend
gatewayd-depend:
	$(KEEP_GOING)@cd Gateway/Gateway && $(MAKE) -f GNUmakefile.gatewayd depend

.PHONY: Gateway_Peer
Gateway_Peer:
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.Gateway_Peer all

.PHONY: Gateway_Peer-depend
Gateway_Peer-depend:
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.Gateway_Peer depend

.PHONY: gateway_peerd
gateway_peerd: Gateway_Peer
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.gateway_peerd all

.PHONY: gateway_peerd-depend
gateway_peerd-depend:
	$(KEEP_GOING)@cd Gateway/Peer && $(MAKE) -f GNUmakefile.gateway_peerd depend

.PHONY: blobby
blobby:
	$(KEEP_GOING)@cd JAWS/clients/Blobby && $(MAKE) -f GNUmakefile.blobby all

.PHONY: blobby-depend
blobby-depend:
	$(KEEP_GOING)@cd JAWS/clients/Blobby && $(MAKE) -f GNUmakefile.blobby depend

.PHONY: http_client
http_client:
	$(KEEP_GOING)@cd JAWS/clients/Caching && $(MAKE) -f GNUmakefile.http_client all

.PHONY: http_client-depend
http_client-depend:
	$(KEEP_GOING)@cd JAWS/clients/Caching && $(MAKE) -f GNUmakefile.http_client depend

.PHONY: JAWS-target
JAWS-target:
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS all

.PHONY: JAWS-target-depend
JAWS-target-depend:
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS depend

.PHONY: JAWS_server
JAWS_server: JAWS-target
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS_server all

.PHONY: JAWS_server-depend
JAWS_server-depend:
	$(KEEP_GOING)@cd JAWS/server && $(MAKE) -f GNUmakefile.JAWS_server depend

.PHONY: JAWS2-target
JAWS2-target:
	$(KEEP_GOING)@cd JAWS2/JAWS && $(MAKE) -f GNUmakefile.JAWS2 all

.PHONY: JAWS2-target-depend
JAWS2-target-depend:
	$(KEEP_GOING)@cd JAWS2/JAWS && $(MAKE) -f GNUmakefile.JAWS2 depend

.PHONY: HTTPU
HTTPU: JAWS2-target
	$(KEEP_GOING)@cd JAWS2/HTTPU && $(MAKE) -f GNUmakefile.HTTPU all

.PHONY: HTTPU-depend
HTTPU-depend:
	$(KEEP_GOING)@cd JAWS2/HTTPU && $(MAKE) -f GNUmakefile.HTTPU depend

.PHONY: JAWS3-target
JAWS3-target:
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3 all

.PHONY: JAWS3-target-depend
JAWS3-target-depend:
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3 depend

.PHONY: JAWS3_server
JAWS3_server: JAWS3-target
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3_server all

.PHONY: JAWS3_server-depend
JAWS3_server-depend:
	$(KEEP_GOING)@cd JAWS3/jaws3 && $(MAKE) -f GNUmakefile.JAWS3_server depend

.PHONY: drwho__server
drwho__server:
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__server all

.PHONY: drwho__server-depend
drwho__server-depend:
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__server depend

.PHONY: drwho__client
drwho__client: drwho__server
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__client all

.PHONY: drwho__client-depend
drwho__client-depend:
	$(KEEP_GOING)@cd drwho && $(MAKE) -f GNUmakefile.drwho__client depend

.PHONY: gperf_docs
gperf_docs:
	$(KEEP_GOING)@cd gperf && $(MAKE) -f GNUmakefile.gperf_docs all

.PHONY: gperf_docs-depend
gperf_docs-depend:
	$(KEEP_GOING)@cd gperf && $(MAKE) -f GNUmakefile.gperf_docs depend

.PHONY: gperf-target
gperf-target:
	$(KEEP_GOING)@cd gperf/src && $(MAKE) -f GNUmakefile.gperf all

.PHONY: gperf-target-depend
gperf-target-depend:
	$(KEEP_GOING)@cd gperf/src && $(MAKE) -f GNUmakefile.gperf depend

.PHONY: cinset
cinset: gperf-target
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cinset all

.PHONY: cinset-depend
cinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cinset depend

.PHONY: adainset
adainset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.adainset all

.PHONY: adainset-depend
adainset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.adainset depend

.PHONY: cppinset
cppinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cppinset all

.PHONY: cppinset-depend
cppinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.cppinset depend

.PHONY: iinset
iinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset all

.PHONY: iinset-depend
iinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset depend

.PHONY: iinset2
iinset2: gperf-target cinset iinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset2 all

.PHONY: iinset2-depend
iinset2-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.iinset2 depend

.PHONY: m3inset
m3inset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.m3inset all

.PHONY: m3inset-depend
m3inset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.m3inset depend

.PHONY: pinset
pinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.pinset all

.PHONY: pinset-depend
pinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.pinset depend

.PHONY: preinset
preinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.preinset all

.PHONY: preinset-depend
preinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.preinset depend

.PHONY: taoinset
taoinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.taoinset all

.PHONY: taoinset-depend
taoinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.taoinset depend

.PHONY: tinset
tinset: gperf-target cinset
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.tinset all

.PHONY: tinset-depend
tinset-depend:
	$(KEEP_GOING)@cd gperf/tests && $(MAKE) -f GNUmakefile.tinset depend

.PHONY: mkcsregdb-target
mkcsregdb-target:
	$(KEEP_GOING)@cd mkcsregdb && $(MAKE) -f GNUmakefile.mkcsregdb all

.PHONY: mkcsregdb-target-depend
mkcsregdb-target-depend:
	$(KEEP_GOING)@cd mkcsregdb && $(MAKE) -f GNUmakefile.mkcsregdb depend

.PHONY: soreduce-target
soreduce-target:
	$(KEEP_GOING)@cd soreduce && $(MAKE) -f GNUmakefile.soreduce all

.PHONY: soreduce-target-depend
soreduce-target-depend:
	$(KEEP_GOING)@cd soreduce && $(MAKE) -f GNUmakefile.soreduce depend

project_name_list:
	@echo Gateway-target
	@echo gatewayd
	@echo Gateway_Peer
	@echo gateway_peerd
	@echo blobby
	@echo http_client
	@echo JAWS-target
	@echo JAWS_server
	@echo HTTPU
	@echo JAWS2-target
	@echo JAWS3-target
	@echo JAWS3_server
	@echo drwho__client
	@echo drwho__server
	@echo gperf_docs
	@echo gperf-target
	@echo adainset
	@echo cinset
	@echo cppinset
	@echo iinset
	@echo iinset2
	@echo m3inset
	@echo pinset
	@echo preinset
	@echo taoinset
	@echo tinset
	@echo mkcsregdb-target
	@echo soreduce-target
