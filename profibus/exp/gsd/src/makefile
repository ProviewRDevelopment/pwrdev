include $(pwre_dir_symbols)

ifndef variables_mk
 include $(pwre_kroot)/tools/bld/src/variables.mk
endif

ifndef rules_mk
 include $(pwre_kroot)/tools/bld/src/rules.mk
endif

vpath %.gsd $(co_source)
vpath %.gse $(co_source)
vpath %.xml $(co_source)

source_dirs := $(co_source)

gsd_sources := $(sort \
             $(foreach file, \
               $(foreach dir, \
                 $(source_dirs), \
                 $(wildcard $(dir)/*.gsd) \
               ), $(notdir $(file)) \
             ) \
           )

gse_sources := $(sort \
             $(foreach file, \
               $(foreach dir, \
                 $(source_dirs), \
                 $(wildcard $(dir)/*.gse) \
               ), $(notdir $(file)) \
             ) \
           )

xml_sources := $(sort \
             $(foreach file, \
               $(foreach dir, \
                 $(source_dirs), \
                 $(wildcard $(dir)/*.xml) \
               ), $(notdir $(file)) \
             ) \
           )

export_gsd := $(patsubst %.gsd, $(exe_dir)/%.gsd, $(gsd_sources))
clean_gsd := $(patsubst %.gsd, clean_%.gsd, $(gsd_sources))
export_gse := $(patsubst %.gse, $(exe_dir)/%.gse, $(gse_sources))
clean_gse := $(patsubst %.gse, clean_%.gse, $(gse_sources))
export_xml := $(patsubst %.xml, $(exe_dir)/%.xml, $(xml_sources))
clean_xml := $(patsubst %.xml, clean_%.xml, $(xml_sources))


.PHONY : all init copy lib exe clean realclean\
         $(clean_gsd) $(clean_gse) $(clean_xml)

all : init copy | silent

init : silent

copy : $(export_gsd) $(export_gse) $(export_xml) | silent

lib : silent

exe : silent

clean :

realclean : clean $(clean_gsd) $(clean_gse) $(clean_xml)

silent :
	@ :

$(export_gsd) : $(exe_dir)/%.gsd : %.gsd
	@ $(log_exp)
	@ $(cp) $(cpflags) $(source) $(target)

$(clean_gsd) : clean_%.gsd : %.gsd
	@ rm $(exe_dir)/$*.gsd

$(export_gse) : $(exe_dir)/%.gse : %.gse
	@ $(log_exp)
	@ $(cp) $(cpflags) $(source) $(target)

$(clean_gse) : clean_%.gse : %.gse
	@ rm $(exe_dir)/$*.gse

$(export_xml) : $(exe_dir)/%.xml : %.xml
	@ $(log_exp)
	@ $(cp) $(cpflags) $(source) $(target)

$(clean_xml) : clean_%.xml : %.xml
	@ rm $(exe_dir)/$*.xml
