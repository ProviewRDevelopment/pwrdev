my : demo_all

include $(pwr_exe)/pwrp_rules.mk

demo_modules = $(pwrp_inc)/ra_plc_user.h \
	       $(pwrp_exe)/ra_status \
	       $(pwrp_exe)/ra_nethtest \
	       $(pwrp_exe)/ra_qcom2test \
	       $(pwrp_exe)/ra_testall_a.sh \
	       $(pwrp_exe)/ra_testall_b.sh \
	       $(pwrp_exe)/ra_plctest \
	       $(pwrp_exe)/ra_gdhtest \
	       $(pwrp_exe)/ra_timetest \
	       $(pwrp_exe)/ra_nettimetest \
	       $(pwrp_exe)/ra_cdhtest \
	       $(pwrp_exe)/ra_errhtest \
	       $(pwrp_exe)/ra_aproctest \
	       $(pwrp_exe)/ra_mhtest \
	       $(pwrp_exe)/ra_mhappltest \
	       $(pwrp_exe)/ra_qcomtest \
	       $(pwrp_exe)/ra_qmontest \
	       $(pwrp_exe)/ra_modbustcptest \
	       $(pwrp_exe)/ra_remotetest \
	       $(pwrp_exe)/ra_iotest \
	       $(pwrp_exe)/ra_pwrrttest.py \
	       $(pwrp_exe)/ra_ccmtest.rtt_com \
	       $(pwrp_exe)/ra_xttscripttest.rtt_com \
	       $(pwrp_exe)/ra_mqtttest.py \
	       $(pwrp_exe)/ra_testall_c.sh \
	       $(pwrp_exe)/ra_sevtest.py \
	       $(pwrp_exe)/ra_sev_mqtttest.py \
	       $(pwrp_exe)/ra_testall_d.sh \
	       $(pwrp_exe)/ra_sevtest_e.py \
	       $(pwrp_exe)/ra_testall_e.sh \
	       $(pwrp_exe)/ra_testall_f.sh \
	       $(pwrp_obj)/ra_plc_user.o



demo_all : $(demo_modules)

$(pwrp_inc)/ra_plc_user.h : $(pwrp_appl)/ra_plc_user.h

$(pwrp_exe)/ra_status : $(pwrp_appl)/ra_status.cpp
	@ echo "Building ra_status"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_rt.o -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt

$(pwrp_exe)/ra_nethtest : $(pwrp_appl)/ra_nethtest.cpp $(pwrp_appl)/ra_nethtest.h
	@ echo "Building ra_nethtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_qcom2test : $(pwrp_appl)/ra_qcom2test.cpp $(pwrp_appl)/ra_qcom2test.h
	@ echo "Building ra_qcom2test"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_testall_a.sh : $(pwrp_appl)/ra_testall_a.sh
	@ echo "Building ra_testall_a"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_testall_b.sh : $(pwrp_appl)/ra_testall_b.sh
	@ echo "Building ra_testall_b"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_plctest : $(pwrp_appl)/ra_plctest.cpp
	@ echo "Building ra_plctest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_rt.o -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_gdhtest : $(pwrp_appl)/ra_gdhtest.cpp $(pwrp_appl)/ra_gdhtest.h
	@ echo "Building ra_gdhtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_timetest : $(pwrp_appl)/ra_timetest.cpp $(pwrp_appl)/ra_timetest.h
	@ echo "Building ra_timetest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_nettimetest : $(pwrp_appl)/ra_nettimetest.cpp $(pwrp_appl)/ra_nettimetest.h
	@ echo "Building ra_nettimetest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_cdhtest : $(pwrp_appl)/ra_cdhtest.cpp $(pwrp_appl)/ra_cdhtest.h
	@ echo "Building ra_cdhtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_errhtest : $(pwrp_appl)/ra_errhtest.cpp $(pwrp_appl)/ra_errhtest.h
	@ echo "Building ra_errhtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_aproctest : $(pwrp_appl)/ra_aproctest.cpp $(pwrp_appl)/ra_aproctest.h
	@ echo "Building ra_aproctest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_mhtest : $(pwrp_appl)/ra_mhtest.cpp $(pwrp_appl)/ra_mhtest.h 
	@ echo "Building ra_mhtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_mhappltest : $(pwrp_appl)/ra_mhappltest.cpp $(pwrp_appl)/ra_mhappltest.h 
	@ echo "Building ra_mhappltest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_qcomtest : $(pwrp_appl)/ra_qcomtest.cpp $(pwrp_appl)/ra_qcomtest.h 
	@ echo "Building ra_qcomtest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_qmontest : $(pwrp_appl)/ra_qmontest.cpp $(pwrp_appl)/ra_qmontest.h 
	@ echo "Building ra_qmontest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_modbustcptest : $(pwrp_appl)/ra_modbustcptest.cpp
	@ echo "Building ra_modbustcptest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_remotetest : $(pwrp_appl)/ra_remotetest.cpp
	@ echo "Building ra_remotetest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_iotest : $(pwrp_appl)/ra_iotest.cpp
	@ echo "Building ra_iotest"
	@ g++ -g -o $(target) $(source) $(pwr_obj)/pwr_msg_co.o $(pwr_obj)/pwr_msg_rt.o $(pwr_obj)/pwr_msg_rs.o -I$(pwrp_inc) -I$(pwr_inc) -I/usr/include/tirpc -L$(pwr_lib) -lpwr_rt -lpwr_co -lpwr_msg_dummy -ltirpc -lpthread -lm -lrt -Wall

$(pwrp_exe)/ra_pwrrttest.py : $(pwrp_appl)/ra_pwrrttest.py
	@ echo "Building ra_pwrrttest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_ccmtest.rtt_com : $(pwrp_appl)/ra_ccmtest.rtt_com
	@ echo "Building ra_ccmtest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_xttscripttest.rtt_com : $(pwrp_appl)/ra_xttscripttest.rtt_com
	@ echo "Building ra_xttscripttest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_mqtttest.py : $(pwrp_appl)/ra_mqtttest.py
	@ echo "Building ra_mqtttest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_testall_c.sh : $(pwrp_appl)/ra_testall_c.sh
	@ echo "Building ra_testall_c"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_sevtest.py : $(pwrp_appl)/ra_sevtest.py
	@ echo "Building ra_sevtest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_sev_mqtttest.py : $(pwrp_appl)/ra_sev_mqtttest.py
	@ echo "Building ra_sev_mqtttest"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_testall_d.sh : $(pwrp_appl)/ra_testall_d.sh
	@ echo "Building ra_testall_d"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_sevtest_e.py : $(pwrp_appl)/ra_sevtest_e.py
	@ echo "Building ra_sevtest_e"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_testall_e.sh : $(pwrp_appl)/ra_testall_e.sh
	@ echo "Building ra_testall_e"
	@ cp -p $(source) $(target)

$(pwrp_exe)/ra_testall_f.sh : $(pwrp_appl)/ra_testall_f.sh
	@ echo "Building ra_testall_f"
	@ cp -p $(source) $(target)

$(pwrp_obj)/ra_plc_user.o : $(pwrp_appl)/ra_plc_user.c
