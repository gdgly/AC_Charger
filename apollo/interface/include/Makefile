# -*- coding: gb2312; -*- 
## 
## ��   ��   ��: makefiletemplate.mk
##
## ��   ��   ��: liangyaozhan
##
## ��        ��: 1.0
##
## ��  �� ��  ��: Sun Mar 25 00:30:37 HKT 2012
##
## ��        ��: 
##              
#########################################################################################################


#auto search base directory
# shell cmd:
# d=`pwd`; while [ ! -d $d/makefiles ]; do d=`dirname $d` ; done ; echo $d
ifeq ($(PROJECT_BASE),)
PROJECT_BASE := $(shell d=`pwd`; while [ ! -d $$d/makefiles ]; do d=`dirname $$d` ; done ; echo $$d)
export PROJECT_BASE
endif
ifeq ($(PROJECT_IMG_BASE),)
PROJECT_IMG_BASE := $(shell d=`pwd`; while [ ! -f $$d/img.mk ] && [ ! -d $$d/makefiles ]  ; do d=`dirname $$d` ; done ; if [ -f $$d/img.mk ]; then echo "$$d"; else echo ""; fi)
export PROJECT_IMG_BASE
endif


#in case we are on a WIN32 host ...
PROJECT_BASE := $(subst \,/,$(PROJECT_BASE))

# ȷ����һ��Ŀ����all
all:pre_building
# ����Ĭ�ϵĹ���
Makefile:;

# �ڶ���Ŀ���ļ�֮ǰ��Ҫ����һЩ���壬�磺CPU
include $(PROJECT_BASE)/makefiles/config.mk

#���뵽$(MODULE_NAME)��Ŀ���ļ�
COBJS   := $(patsubst %.c,%.o,$(wildcard *.c)) 
CPPOBJS := $(patsubst %.cpp,%.o,$(wildcard *.cpp)) 
SOBJS   := $(patsubst %.S,%.o,$(wildcard *.S))

# ��Ŀ¼�����򵽵Ŀ����֣��ڰ�װMakefileʱ�Զ����ɡ�
#<<tree.cfg

#ָ�������������,�����Ŀ¼��ע��ʹ�� "+=" 
CFLAGS +=

# �����뵱ǰĿ¼ʱ��Ҫ�����include·������ɰ�Ŀ¼д�ϡ�ֱ��дĿ¼���ɣ�������Ŀ¼ǰ��"-I".
#INC_PATH += /to/your/local/include/directory
INC_PATH += 


#��make cleanʱ��Ҫ����ɾ�����ļ�.����OBJS�ϵ�Ŀ���ļ�����Ҫ��д�����
# ��yylex.c yylex.h
#EX_CLEAN_FILE += yylex.c yylex.h
EX_CLEAN_FILE += 

# ��ָ����Ŀ¼.��������˱���(��Ҫ����ע��)����������Ŀ¼������.
# ע�⣺��Ҫ��"sinclude $(PROJECT_BASE)/makefiles/rules.mk"֮ǰ����˱���
#ALL_SUB_PATH = subdir1 subdir2 subdir3
# ����Ŀ¼�ı���˳����Ҫʱ���������ļ��ĺ���(��"sinclude $(PROJECT_BASE)/makefiles/rules.mk"֮��)
# ָ����Ŀ¼��������ϵ������ȷ������֮��ı���˳��
# �磺 ��Ŀ¼subdir1,subdir2,subdir3�ı���˳������ subdir1 ==> subdir2 ==> subdir3
#     ���ڴ��ļ�����������ϵ��
#         subdir3:subdir2
#         subdir2:subdir1
# ����д�ڵ�ǰĿ¼��dircfg.mk
# 

EXCLUDE_SUB_PATH :=

# ������ܣ��������ǰĿ¼�µ������ļ�
-include ./dircfg.mk

#
# ����ģ��(��)�����ɹ���
# 
sinclude $(PROJECT_BASE)/makefiles/rules.mk

# �ڱ���OBJS����Ŀ¼ǰ������ʹ�ô�Ŀ�����һЩ����������д��ĳ��Ŀ¼��dircfg.mk��
pre_building:


# �ڱ���OBJS����Ŀ¼�󣬿���ʹ�ô�Ŀ�����һЩ����������д��ĳ��Ŀ¼��dircfg.mk��
post_building:
