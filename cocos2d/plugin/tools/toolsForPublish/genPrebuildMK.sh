SOURCE_FILE_NAME=$1
TARGET_FILE_NAME=$2

echo "LOCAL_PATH := \$(call my-dir)" > ${TARGET_FILE_NAME}
echo "" >> ${TARGET_FILE_NAME}
echo "include \$(CLEAR_VARS)" >> ${TARGET_FILE_NAME}

MODULE_NAME=`cat ${SOURCE_FILE_NAME} | grep LOCAL_MODULE[^_]`
MODULE_FILENAME=`cat ${SOURCE_FILE_NAME} | grep LOCAL_MODULE_FILENAME`

if [ -n "${MODULE_NAME}" ]; then
echo ${MODULE_NAME} >> ${TARGET_FILE_NAME}
fi

if [ -n "${MODULE_FILENAME}" ]; then
echo ${MODULE_FILENAME} >> ${TARGET_FILE_NAME}
LIB_FILENAME=${MODULE_FILENAME#*\=}
else
LIB_FILENAME=${MODULE_NAME#*\=}
fi
LIB_FILENAME=`echo ${LIB_FILENAME} | sed 's/ //g'`
LIB_FILENAME=${LIB_FILENAME}.a

echo "" >> ${TARGET_FILE_NAME}

echo "LOCAL_SRC_FILES := ./lib/"\$\(TARGET_ARCH_ABI\)/${LIB_FILENAME} >> ${TARGET_FILE_NAME}
echo "LOCAL_EXPORT_C_INCLUDES := \$(LOCAL_PATH)/../include \$(LOCAL_PATH)" >> ${TARGET_FILE_NAME}
echo "LOCAL_EXPORT_LDLIBS := -llog" >> ${TARGET_FILE_NAME}

echo "" >> ${TARGET_FILE_NAME}
echo "include \$(PREBUILT_STATIC_LIBRARY)" >> ${TARGET_FILE_NAME}
