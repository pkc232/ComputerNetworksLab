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

all: drwho__server drwho__client

depend: drwho__server-depend drwho__client-depend

REMAINING_TARGETS := $(filter-out all depend,$(TARGETS_NESTED:.nested=)) $(CUSTOM_TARGETS)
.PHONY: $(REMAINING_TARGETS)

$(REMAINING_TARGETS):
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__server $(@)
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__client $(@)

.PHONY: drwho__server
drwho__server:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__server all

.PHONY: drwho__server-depend
drwho__server-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__server depend

.PHONY: drwho__client
drwho__client: drwho__server
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__client all

.PHONY: drwho__client-depend
drwho__client-depend:
	$(KEEP_GOING)@$(MAKE) -f GNUmakefile.drwho__client depend

project_name_list:
	@echo drwho__client
	@echo drwho__server
