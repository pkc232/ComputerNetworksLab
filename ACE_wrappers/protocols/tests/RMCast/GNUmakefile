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

all: RMCast_Receiver RMCast_Sender

depend: RMCast_Receiver-depend RMCast_Sender-depend

REMAINING_TARGETS := $(filter-out all depend,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)
.PHONY: $(REMAINING_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Receiver $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Sender $(@)

.PHONY: RMCast_Receiver
RMCast_Receiver:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Receiver all

.PHONY: RMCast_Receiver-depend
RMCast_Receiver-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Receiver depend

.PHONY: RMCast_Sender
RMCast_Sender:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Sender all

.PHONY: RMCast_Sender-depend
RMCast_Sender-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.RMCast_Sender depend

project_name_list:
	@echo RMCast_Receiver
	@echo RMCast_Sender
