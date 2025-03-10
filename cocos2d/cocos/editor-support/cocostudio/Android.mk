LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := cocostudio_static

LOCAL_MODULE_FILENAME := libcocostudio

LOCAL_ARM_MODE := arm

LOCAL_SRC_FILES := CCActionFrame.cpp \
CCActionFrameEasing.cpp \
CCActionManagerEx.cpp \
CCActionNode.cpp \
CCActionObject.cpp \
CCArmature.cpp \
CCBone.cpp \
CCArmatureAnimation.cpp \
CCProcessBase.cpp \
CCTween.cpp \
CCDatas.cpp \
CCBatchNode.cpp \
CCDecorativeDisplay.cpp \
CCDisplayFactory.cpp \
CCDisplayManager.cpp \
CCSkin.cpp \
CCColliderDetector.cpp \
CCArmatureDataManager.cpp \
CCArmatureDefine.cpp \
CCDataReaderHelper.cpp \
CCSpriteFrameCacheHelper.cpp \
CCTransformHelp.cpp \
CCUtilMath.cpp \
CCComAttribute.cpp \
CCComAudio.cpp \
CCComController.cpp \
CCComRender.cpp \
CCInputDelegate.cpp \
DictionaryHelper.cpp \
LocalizationManager.cpp \
CCSGUIReader.cpp \
CCSSceneReader.cpp \
TriggerBase.cpp \
TriggerMng.cpp \
TriggerObj.cpp \
CocoLoader.cpp \
WidgetReader/NodeReader/NodeReader.cpp \
WidgetReader/SingleNodeReader/SingleNodeReader.cpp \
WidgetReader/SpriteReader/SpriteReader.cpp \
WidgetReader/ParticleReader/ParticleReader.cpp \
WidgetReader/GameMapReader/GameMapReader.cpp \
WidgetReader/ProjectNodeReader/ProjectNodeReader.cpp \
WidgetReader/ComAudioReader/ComAudioReader.cpp \
WidgetReader/WidgetReader.cpp \
WidgetReader/ButtonReader/ButtonReader.cpp \
WidgetReader/CheckBoxReader/CheckBoxReader.cpp \
WidgetReader/ImageViewReader/ImageViewReader.cpp \
WidgetReader/LayoutReader/LayoutReader.cpp \
WidgetReader/ListViewReader/ListViewReader.cpp \
WidgetReader/LoadingBarReader/LoadingBarReader.cpp \
WidgetReader/PageViewReader/PageViewReader.cpp \
WidgetReader/ScrollViewReader/ScrollViewReader.cpp \
WidgetReader/SliderReader/SliderReader.cpp \
WidgetReader/TextAtlasReader/TextAtlasReader.cpp \
WidgetReader/TextBMFontReader/TextBMFontReader.cpp \
WidgetReader/TextFieldReader/TextFieldReader.cpp \
WidgetReader/TextReader/TextReader.cpp \
WidgetReader/Node3DReader/Node3DReader.cpp \
WidgetReader/Sprite3DReader/Sprite3DReader.cpp \
WidgetReader/UserCameraReader/UserCameraReader.cpp \
WidgetReader/Particle3DReader/Particle3DReader.cpp \
WidgetReader/SkeletonReader/BoneNodeReader.cpp \
WidgetReader/SkeletonReader/SkeletonNodeReader.cpp \
WidgetReader/GameNode3DReader/GameNode3DReader.cpp \
WidgetReader/Light3DReader/Light3DReader.cpp \
ActionTimeline/CCActionTimelineCache.cpp \
ActionTimeline/CCFrame.cpp \
ActionTimeline/CCTimeLine.cpp \
ActionTimeline/CCActionTimeline.cpp \
ActionTimeline/CCActionTimelineNode.cpp \
ActionTimeline/CSLoader.cpp \
ActionTimeline/CCBoneNode.cpp \
ActionTimeline/CCSkeletonNode.cpp \
ActionTimeline/CCSkinNode.cpp \
FlatBuffersSerialize.cpp \
WidgetCallBackHandlerProtocol.cpp \
WidgetReader/ArmatureNodeReader/ArmatureNodeReader.cpp \
WidgetReader/TabControlReader/TabControlReader.cpp \
CCComExtensionData.cpp \
CocoStudio.cpp


LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/..

LOCAL_C_INCLUDES := $(LOCAL_PATH)/.. \
                    $(LOCAL_PATH)/WidgetReader

LOCAL_CFLAGS += -fexceptions

LOCAL_STATIC_LIBRARIES := cocos_ui_static
LOCAL_STATIC_LIBRARIES += cocosdenshion_static
LOCAL_STATIC_LIBRARIES += cocos_flatbuffers_static

include $(BUILD_STATIC_LIBRARY)
