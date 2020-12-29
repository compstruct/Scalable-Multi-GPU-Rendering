/////////////////////////////////////////////////
// This file has been automatically generated  //
// Do not modify this file                     //
/////////////////////////////////////////////////

#include "GLIEntryPoints.h"
void GLAPIENTRY glAccum(GLenum op, GLfloat value)
{
    gli().init();
    PREV_USER_CALL(glAccum,glAccum(op,value))
    glCalls().glAccum(op,value);
    POST_USER_CALL(glAccum,glAccum(op,value))
}

void GLAPIENTRY glActiveStencilFaceEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glActiveStencilFaceEXT,glActiveStencilFaceEXT(_p0))
    glCalls().glActiveStencilFaceEXT(_p0);
    POST_USER_CALL(glActiveStencilFaceEXT,glActiveStencilFaceEXT(_p0))
}

void GLAPIENTRY glActiveTexture(GLenum texture)
{
    gli().init();
    PREV_USER_CALL(glActiveTexture,glActiveTexture(texture))
    glCalls().glActiveTexture(texture);
    POST_USER_CALL(glActiveTexture,glActiveTexture(texture))
}

void GLAPIENTRY glActiveTextureARB(GLenum texture)
{
    gli().init();
    PREV_USER_CALL(glActiveTextureARB,glActiveTextureARB(texture))
    glCalls().glActiveTextureARB(texture);
    POST_USER_CALL(glActiveTextureARB,glActiveTextureARB(texture))
}

void GLAPIENTRY glActiveVaryingNV(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    PREV_USER_CALL(glActiveVaryingNV,glActiveVaryingNV(_p0,_p1))
    glCalls().glActiveVaryingNV(_p0,_p1);
    POST_USER_CALL(glActiveVaryingNV,glActiveVaryingNV(_p0,_p1))
}

void GLAPIENTRY glAlphaFragmentOp1ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5)
{
    gli().init();
    PREV_USER_CALL(glAlphaFragmentOp1ATI,glAlphaFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glAlphaFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glAlphaFragmentOp1ATI,glAlphaFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glAlphaFragmentOp2ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6, GLuint _p7, GLuint _p8)
{
    gli().init();
    PREV_USER_CALL(glAlphaFragmentOp2ATI,glAlphaFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glAlphaFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glAlphaFragmentOp2ATI,glAlphaFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glAlphaFragmentOp3ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6, GLuint _p7, GLuint _p8, GLuint _p9, GLuint _p10, GLuint _p11)
{
    gli().init();
    PREV_USER_CALL(glAlphaFragmentOp3ATI,glAlphaFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
    glCalls().glAlphaFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11);
    POST_USER_CALL(glAlphaFragmentOp3ATI,glAlphaFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
}

void GLAPIENTRY glAlphaFunc(GLenum func, GLclampf ref)
{
    gli().init();
    PREV_USER_CALL(glAlphaFunc,glAlphaFunc(func,ref))
    glCalls().glAlphaFunc(func,ref);
    POST_USER_CALL(glAlphaFunc,glAlphaFunc(func,ref))
}

void GLAPIENTRY glApplyTextureEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glApplyTextureEXT,glApplyTextureEXT(_p0))
    glCalls().glApplyTextureEXT(_p0);
    POST_USER_CALL(glApplyTextureEXT,glApplyTextureEXT(_p0))
}

GLboolean GLAPIENTRY glAreProgramsResidentNV(GLsizei _p0, const GLuint *_p1, GLboolean *_p2)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glAreProgramsResidentNV,glAreProgramsResidentNV(_p0,_p1,_p2))
    _result = glCalls().glAreProgramsResidentNV(_p0,_p1,_p2);
    POST_USER_CALL(glAreProgramsResidentNV,glAreProgramsResidentNV(_p0,_p1,_p2))
    return _result;
}

GLboolean GLAPIENTRY glAreTexturesResident(GLsizei n, const GLuint *textures, GLboolean *residences)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glAreTexturesResident,glAreTexturesResident(n,textures,residences))
    _result = glCalls().glAreTexturesResident(n,textures,residences);
    POST_USER_CALL(glAreTexturesResident,glAreTexturesResident(n,textures,residences))
    return _result;
}

GLboolean GLAPIENTRY glAreTexturesResidentEXT(GLsizei _p0, const GLuint *_p1, GLboolean *_p2)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glAreTexturesResidentEXT,glAreTexturesResidentEXT(_p0,_p1,_p2))
    _result = glCalls().glAreTexturesResidentEXT(_p0,_p1,_p2);
    POST_USER_CALL(glAreTexturesResidentEXT,glAreTexturesResidentEXT(_p0,_p1,_p2))
    return _result;
}

void GLAPIENTRY glArrayElement(GLint i)
{
    gli().init();
    PREV_USER_CALL(glArrayElement,glArrayElement(i))
    glCalls().glArrayElement(i);
    POST_USER_CALL(glArrayElement,glArrayElement(i))
}

void GLAPIENTRY glArrayElementEXT(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glArrayElementEXT,glArrayElementEXT(_p0))
    glCalls().glArrayElementEXT(_p0);
    POST_USER_CALL(glArrayElementEXT,glArrayElementEXT(_p0))
}

void GLAPIENTRY glArrayObjectATI(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLuint _p4, GLuint _p5)
{
    gli().init();
    PREV_USER_CALL(glArrayObjectATI,glArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glArrayObjectATI,glArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glAsyncMarkerSGIX(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glAsyncMarkerSGIX,glAsyncMarkerSGIX(_p0))
    glCalls().glAsyncMarkerSGIX(_p0);
    POST_USER_CALL(glAsyncMarkerSGIX,glAsyncMarkerSGIX(_p0))
}

void GLAPIENTRY glAttachObjectARB(GLhandleARB _p0, GLhandleARB _p1)
{
    gli().init();
    PREV_USER_CALL(glAttachObjectARB,glAttachObjectARB(_p0,_p1))
    glCalls().glAttachObjectARB(_p0,_p1);
    POST_USER_CALL(glAttachObjectARB,glAttachObjectARB(_p0,_p1))
}

void GLAPIENTRY glAttachShader(GLuint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glAttachShader,glAttachShader(_p0,_p1))
    glCalls().glAttachShader(_p0,_p1);
    POST_USER_CALL(glAttachShader,glAttachShader(_p0,_p1))
}

void GLAPIENTRY glBegin(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glBegin,glBegin(mode))
    glCalls().glBegin(mode);
    POST_USER_CALL(glBegin,glBegin(mode))
}

void GLAPIENTRY glBeginConditionalRender(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glBeginConditionalRender,glBeginConditionalRender(_p0,_p1))
    glCalls().glBeginConditionalRender(_p0,_p1);
    POST_USER_CALL(glBeginConditionalRender,glBeginConditionalRender(_p0,_p1))
}

void GLAPIENTRY glBeginConditionalRenderNV(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glBeginConditionalRenderNV,glBeginConditionalRenderNV(_p0,_p1))
    glCalls().glBeginConditionalRenderNV(_p0,_p1);
    POST_USER_CALL(glBeginConditionalRenderNV,glBeginConditionalRenderNV(_p0,_p1))
}

void GLAPIENTRY glBeginFragmentShaderATI()
{
    gli().init();
    PREV_USER_CALL(glBeginFragmentShaderATI,glBeginFragmentShaderATI())
    glCalls().glBeginFragmentShaderATI();
    POST_USER_CALL(glBeginFragmentShaderATI,glBeginFragmentShaderATI())
}

void GLAPIENTRY glBeginOcclusionQueryNV(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBeginOcclusionQueryNV,glBeginOcclusionQueryNV(_p0))
    glCalls().glBeginOcclusionQueryNV(_p0);
    POST_USER_CALL(glBeginOcclusionQueryNV,glBeginOcclusionQueryNV(_p0))
}

void GLAPIENTRY glBeginPerfMonitorAMD(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBeginPerfMonitorAMD,glBeginPerfMonitorAMD(_p0))
    glCalls().glBeginPerfMonitorAMD(_p0);
    POST_USER_CALL(glBeginPerfMonitorAMD,glBeginPerfMonitorAMD(_p0))
}

void GLAPIENTRY glBeginQuery(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBeginQuery,glBeginQuery(_p0,_p1))
    glCalls().glBeginQuery(_p0,_p1);
    POST_USER_CALL(glBeginQuery,glBeginQuery(_p0,_p1))
}

void GLAPIENTRY glBeginQueryARB(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBeginQueryARB,glBeginQueryARB(_p0,_p1))
    glCalls().glBeginQueryARB(_p0,_p1);
    POST_USER_CALL(glBeginQueryARB,glBeginQueryARB(_p0,_p1))
}

void GLAPIENTRY glBeginTransformFeedback(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glBeginTransformFeedback,glBeginTransformFeedback(_p0))
    glCalls().glBeginTransformFeedback(_p0);
    POST_USER_CALL(glBeginTransformFeedback,glBeginTransformFeedback(_p0))
}

void GLAPIENTRY glBeginTransformFeedbackEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glBeginTransformFeedbackEXT,glBeginTransformFeedbackEXT(_p0))
    glCalls().glBeginTransformFeedbackEXT(_p0);
    POST_USER_CALL(glBeginTransformFeedbackEXT,glBeginTransformFeedbackEXT(_p0))
}

void GLAPIENTRY glBeginTransformFeedbackNV(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glBeginTransformFeedbackNV,glBeginTransformFeedbackNV(_p0))
    glCalls().glBeginTransformFeedbackNV(_p0);
    POST_USER_CALL(glBeginTransformFeedbackNV,glBeginTransformFeedbackNV(_p0))
}

void GLAPIENTRY glBeginVertexShaderEXT()
{
    gli().init();
    PREV_USER_CALL(glBeginVertexShaderEXT,glBeginVertexShaderEXT())
    glCalls().glBeginVertexShaderEXT();
    POST_USER_CALL(glBeginVertexShaderEXT,glBeginVertexShaderEXT())
}

void GLAPIENTRY glBindAttribLocation(GLuint _p0, GLuint _p1, const GLchar *_p2)
{
    gli().init();
    PREV_USER_CALL(glBindAttribLocation,glBindAttribLocation(_p0,_p1,_p2))
    glCalls().glBindAttribLocation(_p0,_p1,_p2);
    POST_USER_CALL(glBindAttribLocation,glBindAttribLocation(_p0,_p1,_p2))
}

void GLAPIENTRY glBindAttribLocationARB(GLhandleARB _p0, GLuint _p1, const GLcharARB *_p2)
{
    gli().init();
    PREV_USER_CALL(glBindAttribLocationARB,glBindAttribLocationARB(_p0,_p1,_p2))
    glCalls().glBindAttribLocationARB(_p0,_p1,_p2);
    POST_USER_CALL(glBindAttribLocationARB,glBindAttribLocationARB(_p0,_p1,_p2))
}

void GLAPIENTRY glBindBuffer(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindBuffer,glBindBuffer(_p0,_p1))
    glCalls().glBindBuffer(_p0,_p1);
    POST_USER_CALL(glBindBuffer,glBindBuffer(_p0,_p1))
}

void GLAPIENTRY glBindBufferARB(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindBufferARB,glBindBufferARB(_p0,_p1))
    glCalls().glBindBufferARB(_p0,_p1);
    POST_USER_CALL(glBindBufferARB,glBindBufferARB(_p0,_p1))
}

void GLAPIENTRY glBindBufferBase(GLenum _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glBindBufferBase,glBindBufferBase(_p0,_p1,_p2))
    glCalls().glBindBufferBase(_p0,_p1,_p2);
    POST_USER_CALL(glBindBufferBase,glBindBufferBase(_p0,_p1,_p2))
}

void GLAPIENTRY glBindBufferBaseEXT(GLenum _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glBindBufferBaseEXT,glBindBufferBaseEXT(_p0,_p1,_p2))
    glCalls().glBindBufferBaseEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBindBufferBaseEXT,glBindBufferBaseEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBindBufferBaseNV(GLenum _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glBindBufferBaseNV,glBindBufferBaseNV(_p0,_p1,_p2))
    glCalls().glBindBufferBaseNV(_p0,_p1,_p2);
    POST_USER_CALL(glBindBufferBaseNV,glBindBufferBaseNV(_p0,_p1,_p2))
}

void GLAPIENTRY glBindBufferOffsetEXT(GLenum _p0, GLuint _p1, GLuint _p2, GLintptr _p3)
{
    gli().init();
    PREV_USER_CALL(glBindBufferOffsetEXT,glBindBufferOffsetEXT(_p0,_p1,_p2,_p3))
    glCalls().glBindBufferOffsetEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBindBufferOffsetEXT,glBindBufferOffsetEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBindBufferOffsetNV(GLenum _p0, GLuint _p1, GLuint _p2, GLintptr _p3)
{
    gli().init();
    PREV_USER_CALL(glBindBufferOffsetNV,glBindBufferOffsetNV(_p0,_p1,_p2,_p3))
    glCalls().glBindBufferOffsetNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBindBufferOffsetNV,glBindBufferOffsetNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBindBufferRange(GLenum _p0, GLuint _p1, GLuint _p2, GLintptr _p3, GLsizeiptr _p4)
{
    gli().init();
    PREV_USER_CALL(glBindBufferRange,glBindBufferRange(_p0,_p1,_p2,_p3,_p4))
    glCalls().glBindBufferRange(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glBindBufferRange,glBindBufferRange(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glBindBufferRangeEXT(GLenum _p0, GLuint _p1, GLuint _p2, GLintptr _p3, GLsizeiptr _p4)
{
    gli().init();
    PREV_USER_CALL(glBindBufferRangeEXT,glBindBufferRangeEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glBindBufferRangeEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glBindBufferRangeEXT,glBindBufferRangeEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glBindBufferRangeNV(GLenum _p0, GLuint _p1, GLuint _p2, GLintptr _p3, GLsizeiptr _p4)
{
    gli().init();
    PREV_USER_CALL(glBindBufferRangeNV,glBindBufferRangeNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glBindBufferRangeNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glBindBufferRangeNV,glBindBufferRangeNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glBindFragDataLocation(GLuint _p0, GLuint _p1, const GLchar *_p2)
{
    gli().init();
    PREV_USER_CALL(glBindFragDataLocation,glBindFragDataLocation(_p0,_p1,_p2))
    glCalls().glBindFragDataLocation(_p0,_p1,_p2);
    POST_USER_CALL(glBindFragDataLocation,glBindFragDataLocation(_p0,_p1,_p2))
}

void GLAPIENTRY glBindFragDataLocationEXT(GLuint _p0, GLuint _p1, const GLchar *_p2)
{
    gli().init();
    PREV_USER_CALL(glBindFragDataLocationEXT,glBindFragDataLocationEXT(_p0,_p1,_p2))
    glCalls().glBindFragDataLocationEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBindFragDataLocationEXT,glBindFragDataLocationEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBindFragmentShaderATI(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBindFragmentShaderATI,glBindFragmentShaderATI(_p0))
    glCalls().glBindFragmentShaderATI(_p0);
    POST_USER_CALL(glBindFragmentShaderATI,glBindFragmentShaderATI(_p0))
}

void GLAPIENTRY glBindFramebuffer(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindFramebuffer,glBindFramebuffer(_p0,_p1))
    glCalls().glBindFramebuffer(_p0,_p1);
    POST_USER_CALL(glBindFramebuffer,glBindFramebuffer(_p0,_p1))
}

void GLAPIENTRY glBindFramebufferEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindFramebufferEXT,glBindFramebufferEXT(_p0,_p1))
    glCalls().glBindFramebufferEXT(_p0,_p1);
    POST_USER_CALL(glBindFramebufferEXT,glBindFramebufferEXT(_p0,_p1))
}

GLuint GLAPIENTRY glBindLightParameterEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glBindLightParameterEXT,glBindLightParameterEXT(_p0,_p1))
    _result = glCalls().glBindLightParameterEXT(_p0,_p1);
    POST_USER_CALL(glBindLightParameterEXT,glBindLightParameterEXT(_p0,_p1))
    return _result;
}

GLuint GLAPIENTRY glBindMaterialParameterEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glBindMaterialParameterEXT,glBindMaterialParameterEXT(_p0,_p1))
    _result = glCalls().glBindMaterialParameterEXT(_p0,_p1);
    POST_USER_CALL(glBindMaterialParameterEXT,glBindMaterialParameterEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glBindMultiTextureEXT(GLenum _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glBindMultiTextureEXT,glBindMultiTextureEXT(_p0,_p1,_p2))
    glCalls().glBindMultiTextureEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBindMultiTextureEXT,glBindMultiTextureEXT(_p0,_p1,_p2))
}

GLuint GLAPIENTRY glBindParameterEXT(GLenum _p0)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glBindParameterEXT,glBindParameterEXT(_p0))
    _result = glCalls().glBindParameterEXT(_p0);
    POST_USER_CALL(glBindParameterEXT,glBindParameterEXT(_p0))
    return _result;
}

void GLAPIENTRY glBindProgramARB(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindProgramARB,glBindProgramARB(_p0,_p1))
    glCalls().glBindProgramARB(_p0,_p1);
    POST_USER_CALL(glBindProgramARB,glBindProgramARB(_p0,_p1))
}

void GLAPIENTRY glBindProgramNV(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindProgramNV,glBindProgramNV(_p0,_p1))
    glCalls().glBindProgramNV(_p0,_p1);
    POST_USER_CALL(glBindProgramNV,glBindProgramNV(_p0,_p1))
}

void GLAPIENTRY glBindRenderbuffer(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindRenderbuffer,glBindRenderbuffer(_p0,_p1))
    glCalls().glBindRenderbuffer(_p0,_p1);
    POST_USER_CALL(glBindRenderbuffer,glBindRenderbuffer(_p0,_p1))
}

void GLAPIENTRY glBindRenderbufferEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindRenderbufferEXT,glBindRenderbufferEXT(_p0,_p1))
    glCalls().glBindRenderbufferEXT(_p0,_p1);
    POST_USER_CALL(glBindRenderbufferEXT,glBindRenderbufferEXT(_p0,_p1))
}

GLuint GLAPIENTRY glBindTexGenParameterEXT(GLenum _p0, GLenum _p1, GLenum _p2)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glBindTexGenParameterEXT,glBindTexGenParameterEXT(_p0,_p1,_p2))
    _result = glCalls().glBindTexGenParameterEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBindTexGenParameterEXT,glBindTexGenParameterEXT(_p0,_p1,_p2))
    return _result;
}

void GLAPIENTRY glBindTexture(GLenum target, GLuint texture)
{
    gli().init();
    PREV_USER_CALL(glBindTexture,glBindTexture(target,texture))
    glCalls().glBindTexture(target,texture);
    POST_USER_CALL(glBindTexture,glBindTexture(target,texture))
}

void GLAPIENTRY glBindTextureEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindTextureEXT,glBindTextureEXT(_p0,_p1))
    glCalls().glBindTextureEXT(_p0,_p1);
    POST_USER_CALL(glBindTextureEXT,glBindTextureEXT(_p0,_p1))
}

GLuint GLAPIENTRY glBindTextureUnitParameterEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glBindTextureUnitParameterEXT,glBindTextureUnitParameterEXT(_p0,_p1))
    _result = glCalls().glBindTextureUnitParameterEXT(_p0,_p1);
    POST_USER_CALL(glBindTextureUnitParameterEXT,glBindTextureUnitParameterEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glBindTransformFeedbackNV(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glBindTransformFeedbackNV,glBindTransformFeedbackNV(_p0,_p1))
    glCalls().glBindTransformFeedbackNV(_p0,_p1);
    POST_USER_CALL(glBindTransformFeedbackNV,glBindTransformFeedbackNV(_p0,_p1))
}

void GLAPIENTRY glBindVertexArray(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBindVertexArray,glBindVertexArray(_p0))
    glCalls().glBindVertexArray(_p0);
    POST_USER_CALL(glBindVertexArray,glBindVertexArray(_p0))
}

void GLAPIENTRY glBindVertexArrayAPPLE(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBindVertexArrayAPPLE,glBindVertexArrayAPPLE(_p0))
    glCalls().glBindVertexArrayAPPLE(_p0);
    POST_USER_CALL(glBindVertexArrayAPPLE,glBindVertexArrayAPPLE(_p0))
}

void GLAPIENTRY glBindVertexShaderEXT(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glBindVertexShaderEXT,glBindVertexShaderEXT(_p0))
    glCalls().glBindVertexShaderEXT(_p0);
    POST_USER_CALL(glBindVertexShaderEXT,glBindVertexShaderEXT(_p0))
}

void GLAPIENTRY glBinormal3bEXT(GLbyte _p0, GLbyte _p1, GLbyte _p2)
{
    gli().init();
    PREV_USER_CALL(glBinormal3bEXT,glBinormal3bEXT(_p0,_p1,_p2))
    glCalls().glBinormal3bEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormal3bEXT,glBinormal3bEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBinormal3bvEXT(const GLbyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glBinormal3bvEXT,glBinormal3bvEXT(_p0))
    glCalls().glBinormal3bvEXT(_p0);
    POST_USER_CALL(glBinormal3bvEXT,glBinormal3bvEXT(_p0))
}

void GLAPIENTRY glBinormal3dEXT(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glBinormal3dEXT,glBinormal3dEXT(_p0,_p1,_p2))
    glCalls().glBinormal3dEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormal3dEXT,glBinormal3dEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBinormal3dvEXT(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glBinormal3dvEXT,glBinormal3dvEXT(_p0))
    glCalls().glBinormal3dvEXT(_p0);
    POST_USER_CALL(glBinormal3dvEXT,glBinormal3dvEXT(_p0))
}

void GLAPIENTRY glBinormal3fEXT(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glBinormal3fEXT,glBinormal3fEXT(_p0,_p1,_p2))
    glCalls().glBinormal3fEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormal3fEXT,glBinormal3fEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBinormal3fvEXT(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glBinormal3fvEXT,glBinormal3fvEXT(_p0))
    glCalls().glBinormal3fvEXT(_p0);
    POST_USER_CALL(glBinormal3fvEXT,glBinormal3fvEXT(_p0))
}

void GLAPIENTRY glBinormal3iEXT(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glBinormal3iEXT,glBinormal3iEXT(_p0,_p1,_p2))
    glCalls().glBinormal3iEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormal3iEXT,glBinormal3iEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBinormal3ivEXT(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glBinormal3ivEXT,glBinormal3ivEXT(_p0))
    glCalls().glBinormal3ivEXT(_p0);
    POST_USER_CALL(glBinormal3ivEXT,glBinormal3ivEXT(_p0))
}

void GLAPIENTRY glBinormal3sEXT(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glBinormal3sEXT,glBinormal3sEXT(_p0,_p1,_p2))
    glCalls().glBinormal3sEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormal3sEXT,glBinormal3sEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBinormal3svEXT(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glBinormal3svEXT,glBinormal3svEXT(_p0))
    glCalls().glBinormal3svEXT(_p0);
    POST_USER_CALL(glBinormal3svEXT,glBinormal3svEXT(_p0))
}

void GLAPIENTRY glBinormalPointerEXT(GLenum _p0, GLsizei _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glBinormalPointerEXT,glBinormalPointerEXT(_p0,_p1,_p2))
    glCalls().glBinormalPointerEXT(_p0,_p1,_p2);
    POST_USER_CALL(glBinormalPointerEXT,glBinormalPointerEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glBitmap(GLsizei width, GLsizei height, GLfloat xorig, GLfloat yorig, GLfloat xmove, GLfloat ymove, const GLubyte *bitmap)
{
    gli().init();
    PREV_USER_CALL(glBitmap,glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap))
    glCalls().glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap);
    POST_USER_CALL(glBitmap,glBitmap(width,height,xorig,yorig,xmove,ymove,bitmap))
}

void GLAPIENTRY glBlendColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    gli().init();
    PREV_USER_CALL(glBlendColor,glBlendColor(red,green,blue,alpha))
    glCalls().glBlendColor(red,green,blue,alpha);
    POST_USER_CALL(glBlendColor,glBlendColor(red,green,blue,alpha))
}

void GLAPIENTRY glBlendColorEXT(GLclampf _p0, GLclampf _p1, GLclampf _p2, GLclampf _p3)
{
    gli().init();
    PREV_USER_CALL(glBlendColorEXT,glBlendColorEXT(_p0,_p1,_p2,_p3))
    glCalls().glBlendColorEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBlendColorEXT,glBlendColorEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBlendEquation(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glBlendEquation,glBlendEquation(mode))
    glCalls().glBlendEquation(mode);
    POST_USER_CALL(glBlendEquation,glBlendEquation(mode))
}

void GLAPIENTRY glBlendEquationEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glBlendEquationEXT,glBlendEquationEXT(_p0))
    glCalls().glBlendEquationEXT(_p0);
    POST_USER_CALL(glBlendEquationEXT,glBlendEquationEXT(_p0))
}

void GLAPIENTRY glBlendEquationSeparate(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glBlendEquationSeparate,glBlendEquationSeparate(_p0,_p1))
    glCalls().glBlendEquationSeparate(_p0,_p1);
    POST_USER_CALL(glBlendEquationSeparate,glBlendEquationSeparate(_p0,_p1))
}

void GLAPIENTRY glBlendEquationSeparateATI(GLenum modeRGB, GLenum modeA)
{
    gli().init();
    PREV_USER_CALL(glBlendEquationSeparateATI,glBlendEquationSeparateATI(modeRGB,modeA))
    glCalls().glBlendEquationSeparateATI(modeRGB,modeA);
    POST_USER_CALL(glBlendEquationSeparateATI,glBlendEquationSeparateATI(modeRGB,modeA))
}

void GLAPIENTRY glBlendEquationSeparateEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glBlendEquationSeparateEXT,glBlendEquationSeparateEXT(_p0,_p1))
    glCalls().glBlendEquationSeparateEXT(_p0,_p1);
    POST_USER_CALL(glBlendEquationSeparateEXT,glBlendEquationSeparateEXT(_p0,_p1))
}

void GLAPIENTRY glBlendFunc(GLenum sfactor, GLenum dfactor)
{
    gli().init();
    PREV_USER_CALL(glBlendFunc,glBlendFunc(sfactor,dfactor))
    glCalls().glBlendFunc(sfactor,dfactor);
    POST_USER_CALL(glBlendFunc,glBlendFunc(sfactor,dfactor))
}

void GLAPIENTRY glBlendFuncSeparate(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glBlendFuncSeparate,glBlendFuncSeparate(_p0,_p1,_p2,_p3))
    glCalls().glBlendFuncSeparate(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBlendFuncSeparate,glBlendFuncSeparate(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBlendFuncSeparateEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glBlendFuncSeparateEXT,glBlendFuncSeparateEXT(_p0,_p1,_p2,_p3))
    glCalls().glBlendFuncSeparateEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBlendFuncSeparateEXT,glBlendFuncSeparateEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBlendFuncSeparateINGR(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glBlendFuncSeparateINGR,glBlendFuncSeparateINGR(_p0,_p1,_p2,_p3))
    glCalls().glBlendFuncSeparateINGR(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBlendFuncSeparateINGR,glBlendFuncSeparateINGR(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBlitFramebuffer(GLint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLint _p7, GLbitfield _p8, GLenum _p9)
{
    gli().init();
    PREV_USER_CALL(glBlitFramebuffer,glBlitFramebuffer(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glBlitFramebuffer(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glBlitFramebuffer,glBlitFramebuffer(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glBlitFramebufferEXT(GLint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLint _p7, GLbitfield _p8, GLenum _p9)
{
    gli().init();
    PREV_USER_CALL(glBlitFramebufferEXT,glBlitFramebufferEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glBlitFramebufferEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glBlitFramebufferEXT,glBlitFramebufferEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glBufferData(GLenum _p0, GLsizeiptr _p1, const GLvoid *_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glBufferData,glBufferData(_p0,_p1,_p2,_p3))
    glCalls().glBufferData(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBufferData,glBufferData(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBufferDataARB(GLenum _p0, GLsizeiptrARB _p1, const GLvoid *_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glBufferDataARB,glBufferDataARB(_p0,_p1,_p2,_p3))
    glCalls().glBufferDataARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBufferDataARB,glBufferDataARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBufferParameteriAPPLE(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glBufferParameteriAPPLE,glBufferParameteriAPPLE(_p0,_p1,_p2))
    glCalls().glBufferParameteriAPPLE(_p0,_p1,_p2);
    POST_USER_CALL(glBufferParameteriAPPLE,glBufferParameteriAPPLE(_p0,_p1,_p2))
}

void GLAPIENTRY glBufferSubData(GLenum _p0, GLintptr _p1, GLsizeiptr _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glBufferSubData,glBufferSubData(_p0,_p1,_p2,_p3))
    glCalls().glBufferSubData(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBufferSubData,glBufferSubData(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glBufferSubDataARB(GLenum _p0, GLintptrARB _p1, GLsizeiptrARB _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glBufferSubDataARB,glBufferSubDataARB(_p0,_p1,_p2,_p3))
    glCalls().glBufferSubDataARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glBufferSubDataARB,glBufferSubDataARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glCallList(GLuint list)
{
    gli().init();
    PREV_USER_CALL(glCallList,glCallList(list))
    glCalls().glCallList(list);
    POST_USER_CALL(glCallList,glCallList(list))
}

void GLAPIENTRY glCallLists(GLsizei n, GLenum type, const GLvoid *lists)
{
    gli().init();
    PREV_USER_CALL(glCallLists,glCallLists(n,type,lists))
    glCalls().glCallLists(n,type,lists);
    POST_USER_CALL(glCallLists,glCallLists(n,type,lists))
}

GLenum GLAPIENTRY glCheckFramebufferStatus(GLenum _p0)
{
    gli().init();
    GLenum _result;
    PREV_USER_CALL(glCheckFramebufferStatus,glCheckFramebufferStatus(_p0))
    _result = glCalls().glCheckFramebufferStatus(_p0);
    POST_USER_CALL(glCheckFramebufferStatus,glCheckFramebufferStatus(_p0))
    return _result;
}

GLenum GLAPIENTRY glCheckFramebufferStatusEXT(GLenum _p0)
{
    gli().init();
    GLenum _result;
    PREV_USER_CALL(glCheckFramebufferStatusEXT,glCheckFramebufferStatusEXT(_p0))
    _result = glCalls().glCheckFramebufferStatusEXT(_p0);
    POST_USER_CALL(glCheckFramebufferStatusEXT,glCheckFramebufferStatusEXT(_p0))
    return _result;
}

GLenum GLAPIENTRY glCheckNamedFramebufferStatusEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    GLenum _result;
    PREV_USER_CALL(glCheckNamedFramebufferStatusEXT,glCheckNamedFramebufferStatusEXT(_p0,_p1))
    _result = glCalls().glCheckNamedFramebufferStatusEXT(_p0,_p1);
    POST_USER_CALL(glCheckNamedFramebufferStatusEXT,glCheckNamedFramebufferStatusEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glClampColor(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glClampColor,glClampColor(_p0,_p1))
    glCalls().glClampColor(_p0,_p1);
    POST_USER_CALL(glClampColor,glClampColor(_p0,_p1))
}

void GLAPIENTRY glClampColorARB(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glClampColorARB,glClampColorARB(_p0,_p1))
    glCalls().glClampColorARB(_p0,_p1);
    POST_USER_CALL(glClampColorARB,glClampColorARB(_p0,_p1))
}

void GLAPIENTRY glClear(GLbitfield mask)
{
    gli().init();
    PREV_USER_CALL(glClear,glClear(mask))
    glCalls().glClear(mask);
    POST_USER_CALL(glClear,glClear(mask))
}

void GLAPIENTRY glClearAccum(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    gli().init();
    PREV_USER_CALL(glClearAccum,glClearAccum(red,green,blue,alpha))
    glCalls().glClearAccum(red,green,blue,alpha);
    POST_USER_CALL(glClearAccum,glClearAccum(red,green,blue,alpha))
}

void GLAPIENTRY glClearBufferfi(GLenum _p0, GLint _p1, GLfloat _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glClearBufferfi,glClearBufferfi(_p0,_p1,_p2,_p3))
    glCalls().glClearBufferfi(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glClearBufferfi,glClearBufferfi(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glClearBufferfv(GLenum _p0, GLint _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glClearBufferfv,glClearBufferfv(_p0,_p1,_p2))
    glCalls().glClearBufferfv(_p0,_p1,_p2);
    POST_USER_CALL(glClearBufferfv,glClearBufferfv(_p0,_p1,_p2))
}

void GLAPIENTRY glClearBufferiv(GLenum _p0, GLint _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glClearBufferiv,glClearBufferiv(_p0,_p1,_p2))
    glCalls().glClearBufferiv(_p0,_p1,_p2);
    POST_USER_CALL(glClearBufferiv,glClearBufferiv(_p0,_p1,_p2))
}

void GLAPIENTRY glClearBufferuiv(GLenum _p0, GLint _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glClearBufferuiv,glClearBufferuiv(_p0,_p1,_p2))
    glCalls().glClearBufferuiv(_p0,_p1,_p2);
    POST_USER_CALL(glClearBufferuiv,glClearBufferuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glClearColor(GLclampf red, GLclampf green, GLclampf blue, GLclampf alpha)
{
    gli().init();
    PREV_USER_CALL(glClearColor,glClearColor(red,green,blue,alpha))
    glCalls().glClearColor(red,green,blue,alpha);
    POST_USER_CALL(glClearColor,glClearColor(red,green,blue,alpha))
}

void GLAPIENTRY glClearColorIiEXT(GLint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glClearColorIiEXT,glClearColorIiEXT(_p0,_p1,_p2,_p3))
    glCalls().glClearColorIiEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glClearColorIiEXT,glClearColorIiEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glClearColorIuiEXT(GLuint _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glClearColorIuiEXT,glClearColorIuiEXT(_p0,_p1,_p2,_p3))
    glCalls().glClearColorIuiEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glClearColorIuiEXT,glClearColorIuiEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glClearDepth(GLclampd depth)
{
    gli().init();
    PREV_USER_CALL(glClearDepth,glClearDepth(depth))
    glCalls().glClearDepth(depth);
    POST_USER_CALL(glClearDepth,glClearDepth(depth))
}

void GLAPIENTRY glClearDepthdNV(GLdouble _p0)
{
    gli().init();
    PREV_USER_CALL(glClearDepthdNV,glClearDepthdNV(_p0))
    glCalls().glClearDepthdNV(_p0);
    POST_USER_CALL(glClearDepthdNV,glClearDepthdNV(_p0))
}

void GLAPIENTRY glClearIndex(GLfloat c)
{
    gli().init();
    PREV_USER_CALL(glClearIndex,glClearIndex(c))
    glCalls().glClearIndex(c);
    POST_USER_CALL(glClearIndex,glClearIndex(c))
}

void GLAPIENTRY glClearStencil(GLint s)
{
    gli().init();
    PREV_USER_CALL(glClearStencil,glClearStencil(s))
    glCalls().glClearStencil(s);
    POST_USER_CALL(glClearStencil,glClearStencil(s))
}

void GLAPIENTRY glClientActiveTexture(GLenum texture)
{
    gli().init();
    PREV_USER_CALL(glClientActiveTexture,glClientActiveTexture(texture))
    glCalls().glClientActiveTexture(texture);
    POST_USER_CALL(glClientActiveTexture,glClientActiveTexture(texture))
}

void GLAPIENTRY glClientActiveTextureARB(GLenum texture)
{
    gli().init();
    PREV_USER_CALL(glClientActiveTextureARB,glClientActiveTextureARB(texture))
    glCalls().glClientActiveTextureARB(texture);
    POST_USER_CALL(glClientActiveTextureARB,glClientActiveTextureARB(texture))
}

void GLAPIENTRY glClientActiveVertexStreamATI(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glClientActiveVertexStreamATI,glClientActiveVertexStreamATI(_p0))
    glCalls().glClientActiveVertexStreamATI(_p0);
    POST_USER_CALL(glClientActiveVertexStreamATI,glClientActiveVertexStreamATI(_p0))
}

void GLAPIENTRY glClientAttribDefaultEXT(GLbitfield _p0)
{
    gli().init();
    PREV_USER_CALL(glClientAttribDefaultEXT,glClientAttribDefaultEXT(_p0))
    glCalls().glClientAttribDefaultEXT(_p0);
    POST_USER_CALL(glClientAttribDefaultEXT,glClientAttribDefaultEXT(_p0))
}

void GLAPIENTRY glClipPlane(GLenum plane, const GLdouble *equation)
{
    gli().init();
    PREV_USER_CALL(glClipPlane,glClipPlane(plane,equation))
    glCalls().glClipPlane(plane,equation);
    POST_USER_CALL(glClipPlane,glClipPlane(plane,equation))
}

void GLAPIENTRY glColor3b(GLbyte red, GLbyte green, GLbyte blue)
{
    gli().init();
    PREV_USER_CALL(glColor3b,glColor3b(red,green,blue))
    glCalls().glColor3b(red,green,blue);
    POST_USER_CALL(glColor3b,glColor3b(red,green,blue))
}

void GLAPIENTRY glColor3bv(const GLbyte *v)
{
    gli().init();
    PREV_USER_CALL(glColor3bv,glColor3bv(v))
    glCalls().glColor3bv(v);
    POST_USER_CALL(glColor3bv,glColor3bv(v))
}

void GLAPIENTRY glColor3d(GLdouble red, GLdouble green, GLdouble blue)
{
    gli().init();
    PREV_USER_CALL(glColor3d,glColor3d(red,green,blue))
    glCalls().glColor3d(red,green,blue);
    POST_USER_CALL(glColor3d,glColor3d(red,green,blue))
}

void GLAPIENTRY glColor3dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glColor3dv,glColor3dv(v))
    glCalls().glColor3dv(v);
    POST_USER_CALL(glColor3dv,glColor3dv(v))
}

void GLAPIENTRY glColor3f(GLfloat red, GLfloat green, GLfloat blue)
{
    gli().init();
    PREV_USER_CALL(glColor3f,glColor3f(red,green,blue))
    glCalls().glColor3f(red,green,blue);
    POST_USER_CALL(glColor3f,glColor3f(red,green,blue))
}

void GLAPIENTRY glColor3fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glColor3fv,glColor3fv(v))
    glCalls().glColor3fv(v);
    POST_USER_CALL(glColor3fv,glColor3fv(v))
}

void GLAPIENTRY glColor3hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glColor3hNV,glColor3hNV(_p0,_p1,_p2))
    glCalls().glColor3hNV(_p0,_p1,_p2);
    POST_USER_CALL(glColor3hNV,glColor3hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glColor3hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glColor3hvNV,glColor3hvNV(_p0))
    glCalls().glColor3hvNV(_p0);
    POST_USER_CALL(glColor3hvNV,glColor3hvNV(_p0))
}

void GLAPIENTRY glColor3i(GLint red, GLint green, GLint blue)
{
    gli().init();
    PREV_USER_CALL(glColor3i,glColor3i(red,green,blue))
    glCalls().glColor3i(red,green,blue);
    POST_USER_CALL(glColor3i,glColor3i(red,green,blue))
}

void GLAPIENTRY glColor3iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glColor3iv,glColor3iv(v))
    glCalls().glColor3iv(v);
    POST_USER_CALL(glColor3iv,glColor3iv(v))
}

void GLAPIENTRY glColor3s(GLshort red, GLshort green, GLshort blue)
{
    gli().init();
    PREV_USER_CALL(glColor3s,glColor3s(red,green,blue))
    glCalls().glColor3s(red,green,blue);
    POST_USER_CALL(glColor3s,glColor3s(red,green,blue))
}

void GLAPIENTRY glColor3sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glColor3sv,glColor3sv(v))
    glCalls().glColor3sv(v);
    POST_USER_CALL(glColor3sv,glColor3sv(v))
}

void GLAPIENTRY glColor3ub(GLubyte red, GLubyte green, GLubyte blue)
{
    gli().init();
    PREV_USER_CALL(glColor3ub,glColor3ub(red,green,blue))
    glCalls().glColor3ub(red,green,blue);
    POST_USER_CALL(glColor3ub,glColor3ub(red,green,blue))
}

void GLAPIENTRY glColor3ubv(const GLubyte *v)
{
    gli().init();
    PREV_USER_CALL(glColor3ubv,glColor3ubv(v))
    glCalls().glColor3ubv(v);
    POST_USER_CALL(glColor3ubv,glColor3ubv(v))
}

void GLAPIENTRY glColor3ui(GLuint red, GLuint green, GLuint blue)
{
    gli().init();
    PREV_USER_CALL(glColor3ui,glColor3ui(red,green,blue))
    glCalls().glColor3ui(red,green,blue);
    POST_USER_CALL(glColor3ui,glColor3ui(red,green,blue))
}

void GLAPIENTRY glColor3uiv(const GLuint *v)
{
    gli().init();
    PREV_USER_CALL(glColor3uiv,glColor3uiv(v))
    glCalls().glColor3uiv(v);
    POST_USER_CALL(glColor3uiv,glColor3uiv(v))
}

void GLAPIENTRY glColor3us(GLushort red, GLushort green, GLushort blue)
{
    gli().init();
    PREV_USER_CALL(glColor3us,glColor3us(red,green,blue))
    glCalls().glColor3us(red,green,blue);
    POST_USER_CALL(glColor3us,glColor3us(red,green,blue))
}

void GLAPIENTRY glColor3usv(const GLushort *v)
{
    gli().init();
    PREV_USER_CALL(glColor3usv,glColor3usv(v))
    glCalls().glColor3usv(v);
    POST_USER_CALL(glColor3usv,glColor3usv(v))
}

void GLAPIENTRY glColor4b(GLbyte red, GLbyte green, GLbyte blue, GLbyte alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4b,glColor4b(red,green,blue,alpha))
    glCalls().glColor4b(red,green,blue,alpha);
    POST_USER_CALL(glColor4b,glColor4b(red,green,blue,alpha))
}

void GLAPIENTRY glColor4bv(const GLbyte *v)
{
    gli().init();
    PREV_USER_CALL(glColor4bv,glColor4bv(v))
    glCalls().glColor4bv(v);
    POST_USER_CALL(glColor4bv,glColor4bv(v))
}

void GLAPIENTRY glColor4d(GLdouble red, GLdouble green, GLdouble blue, GLdouble alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4d,glColor4d(red,green,blue,alpha))
    glCalls().glColor4d(red,green,blue,alpha);
    POST_USER_CALL(glColor4d,glColor4d(red,green,blue,alpha))
}

void GLAPIENTRY glColor4dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glColor4dv,glColor4dv(v))
    glCalls().glColor4dv(v);
    POST_USER_CALL(glColor4dv,glColor4dv(v))
}

void GLAPIENTRY glColor4f(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4f,glColor4f(red,green,blue,alpha))
    glCalls().glColor4f(red,green,blue,alpha);
    POST_USER_CALL(glColor4f,glColor4f(red,green,blue,alpha))
}

void GLAPIENTRY glColor4fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glColor4fv,glColor4fv(v))
    glCalls().glColor4fv(v);
    POST_USER_CALL(glColor4fv,glColor4fv(v))
}

void GLAPIENTRY glColor4hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3)
{
    gli().init();
    PREV_USER_CALL(glColor4hNV,glColor4hNV(_p0,_p1,_p2,_p3))
    glCalls().glColor4hNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glColor4hNV,glColor4hNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glColor4hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glColor4hvNV,glColor4hvNV(_p0))
    glCalls().glColor4hvNV(_p0);
    POST_USER_CALL(glColor4hvNV,glColor4hvNV(_p0))
}

void GLAPIENTRY glColor4i(GLint red, GLint green, GLint blue, GLint alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4i,glColor4i(red,green,blue,alpha))
    glCalls().glColor4i(red,green,blue,alpha);
    POST_USER_CALL(glColor4i,glColor4i(red,green,blue,alpha))
}

void GLAPIENTRY glColor4iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glColor4iv,glColor4iv(v))
    glCalls().glColor4iv(v);
    POST_USER_CALL(glColor4iv,glColor4iv(v))
}

void GLAPIENTRY glColor4s(GLshort red, GLshort green, GLshort blue, GLshort alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4s,glColor4s(red,green,blue,alpha))
    glCalls().glColor4s(red,green,blue,alpha);
    POST_USER_CALL(glColor4s,glColor4s(red,green,blue,alpha))
}

void GLAPIENTRY glColor4sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glColor4sv,glColor4sv(v))
    glCalls().glColor4sv(v);
    POST_USER_CALL(glColor4sv,glColor4sv(v))
}

void GLAPIENTRY glColor4ub(GLubyte red, GLubyte green, GLubyte blue, GLubyte alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4ub,glColor4ub(red,green,blue,alpha))
    glCalls().glColor4ub(red,green,blue,alpha);
    POST_USER_CALL(glColor4ub,glColor4ub(red,green,blue,alpha))
}

void GLAPIENTRY glColor4ubv(const GLubyte *v)
{
    gli().init();
    PREV_USER_CALL(glColor4ubv,glColor4ubv(v))
    glCalls().glColor4ubv(v);
    POST_USER_CALL(glColor4ubv,glColor4ubv(v))
}

void GLAPIENTRY glColor4ui(GLuint red, GLuint green, GLuint blue, GLuint alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4ui,glColor4ui(red,green,blue,alpha))
    glCalls().glColor4ui(red,green,blue,alpha);
    POST_USER_CALL(glColor4ui,glColor4ui(red,green,blue,alpha))
}

void GLAPIENTRY glColor4uiv(const GLuint *v)
{
    gli().init();
    PREV_USER_CALL(glColor4uiv,glColor4uiv(v))
    glCalls().glColor4uiv(v);
    POST_USER_CALL(glColor4uiv,glColor4uiv(v))
}

void GLAPIENTRY glColor4us(GLushort red, GLushort green, GLushort blue, GLushort alpha)
{
    gli().init();
    PREV_USER_CALL(glColor4us,glColor4us(red,green,blue,alpha))
    glCalls().glColor4us(red,green,blue,alpha);
    POST_USER_CALL(glColor4us,glColor4us(red,green,blue,alpha))
}

void GLAPIENTRY glColor4usv(const GLushort *v)
{
    gli().init();
    PREV_USER_CALL(glColor4usv,glColor4usv(v))
    glCalls().glColor4usv(v);
    POST_USER_CALL(glColor4usv,glColor4usv(v))
}

void GLAPIENTRY glColorFragmentOp1ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6)
{
    gli().init();
    PREV_USER_CALL(glColorFragmentOp1ATI,glColorFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glColorFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glColorFragmentOp1ATI,glColorFragmentOp1ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glColorFragmentOp2ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6, GLuint _p7, GLuint _p8, GLuint _p9)
{
    gli().init();
    PREV_USER_CALL(glColorFragmentOp2ATI,glColorFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glColorFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glColorFragmentOp2ATI,glColorFragmentOp2ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glColorFragmentOp3ATI(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6, GLuint _p7, GLuint _p8, GLuint _p9, GLuint _p10, GLuint _p11, GLuint _p12)
{
    gli().init();
    PREV_USER_CALL(glColorFragmentOp3ATI,glColorFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
    glCalls().glColorFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12);
    POST_USER_CALL(glColorFragmentOp3ATI,glColorFragmentOp3ATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
}

void GLAPIENTRY glColorMask(GLboolean red, GLboolean green, GLboolean blue, GLboolean alpha)
{
    gli().init();
    PREV_USER_CALL(glColorMask,glColorMask(red,green,blue,alpha))
    glCalls().glColorMask(red,green,blue,alpha);
    POST_USER_CALL(glColorMask,glColorMask(red,green,blue,alpha))
}

void GLAPIENTRY glColorMaskIndexedEXT(GLuint _p0, GLboolean _p1, GLboolean _p2, GLboolean _p3, GLboolean _p4)
{
    gli().init();
    PREV_USER_CALL(glColorMaskIndexedEXT,glColorMaskIndexedEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glColorMaskIndexedEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glColorMaskIndexedEXT,glColorMaskIndexedEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glColorMaski(GLuint _p0, GLboolean _p1, GLboolean _p2, GLboolean _p3, GLboolean _p4)
{
    gli().init();
    PREV_USER_CALL(glColorMaski,glColorMaski(_p0,_p1,_p2,_p3,_p4))
    glCalls().glColorMaski(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glColorMaski,glColorMaski(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glColorMaterial(GLenum face, GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glColorMaterial,glColorMaterial(face,mode))
    glCalls().glColorMaterial(face,mode);
    POST_USER_CALL(glColorMaterial,glColorMaterial(face,mode))
}

void GLAPIENTRY glColorPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glColorPointer,glColorPointer(size,type,stride,ptr))
    glCalls().glColorPointer(size,type,stride,ptr);
    POST_USER_CALL(glColorPointer,glColorPointer(size,type,stride,ptr))
}

void GLAPIENTRY glColorPointerEXT(GLint _p0, GLenum _p1, GLsizei _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glColorPointerEXT,glColorPointerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glColorPointerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glColorPointerEXT,glColorPointerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glColorPointervINTEL(GLint _p0, GLenum _p1, const GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glColorPointervINTEL,glColorPointervINTEL(_p0,_p1,_p2))
    glCalls().glColorPointervINTEL(_p0,_p1,_p2);
    POST_USER_CALL(glColorPointervINTEL,glColorPointervINTEL(_p0,_p1,_p2))
}

void GLAPIENTRY glColorSubTable(GLenum target, GLsizei start, GLsizei count, GLenum format, GLenum type, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glColorSubTable,glColorSubTable(target,start,count,format,type,data))
    glCalls().glColorSubTable(target,start,count,format,type,data);
    POST_USER_CALL(glColorSubTable,glColorSubTable(target,start,count,format,type,data))
}

void GLAPIENTRY glColorSubTableEXT(GLenum _p0, GLsizei _p1, GLsizei _p2, GLenum _p3, GLenum _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glColorSubTableEXT,glColorSubTableEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glColorSubTableEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glColorSubTableEXT,glColorSubTableEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glColorTable(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *table)
{
    gli().init();
    PREV_USER_CALL(glColorTable,glColorTable(target,internalformat,width,format,type,table))
    glCalls().glColorTable(target,internalformat,width,format,type,table);
    POST_USER_CALL(glColorTable,glColorTable(target,internalformat,width,format,type,table))
}

void GLAPIENTRY glColorTableEXT(GLenum _p0, GLenum _p1, GLsizei _p2, GLenum _p3, GLenum _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glColorTableEXT,glColorTableEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glColorTableEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glColorTableEXT,glColorTableEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glColorTableParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glColorTableParameterfv,glColorTableParameterfv(target,pname,params))
    glCalls().glColorTableParameterfv(target,pname,params);
    POST_USER_CALL(glColorTableParameterfv,glColorTableParameterfv(target,pname,params))
}

void GLAPIENTRY glColorTableParameterfvSGI(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glColorTableParameterfvSGI,glColorTableParameterfvSGI(_p0,_p1,_p2))
    glCalls().glColorTableParameterfvSGI(_p0,_p1,_p2);
    POST_USER_CALL(glColorTableParameterfvSGI,glColorTableParameterfvSGI(_p0,_p1,_p2))
}

void GLAPIENTRY glColorTableParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glColorTableParameteriv,glColorTableParameteriv(target,pname,params))
    glCalls().glColorTableParameteriv(target,pname,params);
    POST_USER_CALL(glColorTableParameteriv,glColorTableParameteriv(target,pname,params))
}

void GLAPIENTRY glColorTableParameterivSGI(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glColorTableParameterivSGI,glColorTableParameterivSGI(_p0,_p1,_p2))
    glCalls().glColorTableParameterivSGI(_p0,_p1,_p2);
    POST_USER_CALL(glColorTableParameterivSGI,glColorTableParameterivSGI(_p0,_p1,_p2))
}

void GLAPIENTRY glColorTableSGI(GLenum _p0, GLenum _p1, GLsizei _p2, GLenum _p3, GLenum _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glColorTableSGI,glColorTableSGI(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glColorTableSGI(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glColorTableSGI,glColorTableSGI(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glCombinerInputNV(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3, GLenum _p4, GLenum _p5)
{
    gli().init();
    PREV_USER_CALL(glCombinerInputNV,glCombinerInputNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glCombinerInputNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glCombinerInputNV,glCombinerInputNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glCombinerOutputNV(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3, GLenum _p4, GLenum _p5, GLenum _p6, GLboolean _p7, GLboolean _p8, GLboolean _p9)
{
    gli().init();
    PREV_USER_CALL(glCombinerOutputNV,glCombinerOutputNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCombinerOutputNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCombinerOutputNV,glCombinerOutputNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCombinerParameterfNV(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glCombinerParameterfNV,glCombinerParameterfNV(_p0,_p1))
    glCalls().glCombinerParameterfNV(_p0,_p1);
    POST_USER_CALL(glCombinerParameterfNV,glCombinerParameterfNV(_p0,_p1))
}

void GLAPIENTRY glCombinerParameterfvNV(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glCombinerParameterfvNV,glCombinerParameterfvNV(_p0,_p1))
    glCalls().glCombinerParameterfvNV(_p0,_p1);
    POST_USER_CALL(glCombinerParameterfvNV,glCombinerParameterfvNV(_p0,_p1))
}

void GLAPIENTRY glCombinerParameteriNV(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glCombinerParameteriNV,glCombinerParameteriNV(_p0,_p1))
    glCalls().glCombinerParameteriNV(_p0,_p1);
    POST_USER_CALL(glCombinerParameteriNV,glCombinerParameteriNV(_p0,_p1))
}

void GLAPIENTRY glCombinerParameterivNV(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glCombinerParameterivNV,glCombinerParameterivNV(_p0,_p1))
    glCalls().glCombinerParameterivNV(_p0,_p1);
    POST_USER_CALL(glCombinerParameterivNV,glCombinerParameterivNV(_p0,_p1))
}

void GLAPIENTRY glCombinerStageParameterfvNV(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glCombinerStageParameterfvNV,glCombinerStageParameterfvNV(_p0,_p1,_p2))
    glCalls().glCombinerStageParameterfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glCombinerStageParameterfvNV,glCombinerStageParameterfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glCompileShader(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glCompileShader,glCompileShader(_p0))
    glCalls().glCompileShader(_p0);
    POST_USER_CALL(glCompileShader,glCompileShader(_p0))
}

void GLAPIENTRY glCompileShaderARB(GLhandleARB _p0)
{
    gli().init();
    PREV_USER_CALL(glCompileShaderARB,glCompileShaderARB(_p0))
    glCalls().glCompileShaderARB(_p0);
    POST_USER_CALL(glCompileShaderARB,glCompileShaderARB(_p0))
}

void GLAPIENTRY glCompressedMultiTexImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLint _p5, GLsizei _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexImage1DEXT,glCompressedMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCompressedMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCompressedMultiTexImage1DEXT,glCompressedMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCompressedMultiTexImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLsizei _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexImage2DEXT,glCompressedMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCompressedMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCompressedMultiTexImage2DEXT,glCompressedMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCompressedMultiTexImage3DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLsizei _p6, GLint _p7, GLsizei _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexImage3DEXT,glCompressedMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCompressedMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCompressedMultiTexImage3DEXT,glCompressedMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCompressedMultiTexSubImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4, GLenum _p5, GLsizei _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexSubImage1DEXT,glCompressedMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCompressedMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCompressedMultiTexSubImage1DEXT,glCompressedMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCompressedMultiTexSubImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLenum _p7, GLsizei _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexSubImage2DEXT,glCompressedMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCompressedMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCompressedMultiTexSubImage2DEXT,glCompressedMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCompressedMultiTexSubImage3DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLsizei _p8, GLenum _p9, GLsizei _p10, const GLvoid *_p11)
{
    gli().init();
    PREV_USER_CALL(glCompressedMultiTexSubImage3DEXT,glCompressedMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
    glCalls().glCompressedMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11);
    POST_USER_CALL(glCompressedMultiTexSubImage3DEXT,glCompressedMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
}

void GLAPIENTRY glCompressedTexImage1D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLint border, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage1D,glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data))
    glCalls().glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data);
    POST_USER_CALL(glCompressedTexImage1D,glCompressedTexImage1D(target,level,internalformat,width,border,imageSize,data))
}

void GLAPIENTRY glCompressedTexImage1DARB(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLint _p4, GLsizei _p5, const GLvoid *_p6)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage1DARB,glCompressedTexImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glCompressedTexImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glCompressedTexImage1DARB,glCompressedTexImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glCompressedTexImage2D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLint border, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage2D,glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data))
    glCalls().glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data);
    POST_USER_CALL(glCompressedTexImage2D,glCompressedTexImage2D(target,level,internalformat,width,height,border,imageSize,data))
}

void GLAPIENTRY glCompressedTexImage2DARB(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLint _p5, GLsizei _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage2DARB,glCompressedTexImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCompressedTexImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCompressedTexImage2DARB,glCompressedTexImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCompressedTexImage3D(GLenum target, GLint level, GLenum internalformat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage3D,glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data))
    glCalls().glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data);
    POST_USER_CALL(glCompressedTexImage3D,glCompressedTexImage3D(target,level,internalformat,width,height,depth,border,imageSize,data))
}

void GLAPIENTRY glCompressedTexImage3DARB(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLsizei _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexImage3DARB,glCompressedTexImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCompressedTexImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCompressedTexImage3DARB,glCompressedTexImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCompressedTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage1D,glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data))
    glCalls().glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data);
    POST_USER_CALL(glCompressedTexSubImage1D,glCompressedTexSubImage1D(target,level,xoffset,width,format,imageSize,data))
}

void GLAPIENTRY glCompressedTexSubImage1DARB(GLenum _p0, GLint _p1, GLint _p2, GLsizei _p3, GLenum _p4, GLsizei _p5, const GLvoid *_p6)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage1DARB,glCompressedTexSubImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glCompressedTexSubImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glCompressedTexSubImage1DARB,glCompressedTexSubImage1DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glCompressedTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage2D,glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data))
    glCalls().glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data);
    POST_USER_CALL(glCompressedTexSubImage2D,glCompressedTexSubImage2D(target,level,xoffset,yoffset,width,height,format,imageSize,data))
}

void GLAPIENTRY glCompressedTexSubImage2DARB(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLsizei _p4, GLsizei _p5, GLenum _p6, GLsizei _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage2DARB,glCompressedTexSubImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCompressedTexSubImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCompressedTexSubImage2DARB,glCompressedTexSubImage2DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCompressedTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLsizei imageSize, const GLvoid *data)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage3D,glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data))
    glCalls().glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data);
    POST_USER_CALL(glCompressedTexSubImage3D,glCompressedTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,imageSize,data))
}

void GLAPIENTRY glCompressedTexSubImage3DARB(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLsizei _p7, GLenum _p8, GLsizei _p9, const GLvoid *_p10)
{
    gli().init();
    PREV_USER_CALL(glCompressedTexSubImage3DARB,glCompressedTexSubImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glCompressedTexSubImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glCompressedTexSubImage3DARB,glCompressedTexSubImage3DARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glCompressedTextureImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLint _p5, GLsizei _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureImage1DEXT,glCompressedTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCompressedTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCompressedTextureImage1DEXT,glCompressedTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCompressedTextureImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLsizei _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureImage2DEXT,glCompressedTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCompressedTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCompressedTextureImage2DEXT,glCompressedTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCompressedTextureImage3DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLsizei _p6, GLint _p7, GLsizei _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureImage3DEXT,glCompressedTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCompressedTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCompressedTextureImage3DEXT,glCompressedTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCompressedTextureSubImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4, GLenum _p5, GLsizei _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureSubImage1DEXT,glCompressedTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCompressedTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCompressedTextureSubImage1DEXT,glCompressedTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCompressedTextureSubImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLenum _p7, GLsizei _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureSubImage2DEXT,glCompressedTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCompressedTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCompressedTextureSubImage2DEXT,glCompressedTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCompressedTextureSubImage3DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLsizei _p8, GLenum _p9, GLsizei _p10, const GLvoid *_p11)
{
    gli().init();
    PREV_USER_CALL(glCompressedTextureSubImage3DEXT,glCompressedTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
    glCalls().glCompressedTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11);
    POST_USER_CALL(glCompressedTextureSubImage3DEXT,glCompressedTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
}

void GLAPIENTRY glConvolutionFilter1D(GLenum target, GLenum internalformat, GLsizei width, GLenum format, GLenum type, const GLvoid *image)
{
    gli().init();
    PREV_USER_CALL(glConvolutionFilter1D,glConvolutionFilter1D(target,internalformat,width,format,type,image))
    glCalls().glConvolutionFilter1D(target,internalformat,width,format,type,image);
    POST_USER_CALL(glConvolutionFilter1D,glConvolutionFilter1D(target,internalformat,width,format,type,image))
}

void GLAPIENTRY glConvolutionFilter1DEXT(GLenum _p0, GLenum _p1, GLsizei _p2, GLenum _p3, GLenum _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glConvolutionFilter1DEXT,glConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glConvolutionFilter1DEXT,glConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glConvolutionFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *image)
{
    gli().init();
    PREV_USER_CALL(glConvolutionFilter2D,glConvolutionFilter2D(target,internalformat,width,height,format,type,image))
    glCalls().glConvolutionFilter2D(target,internalformat,width,height,format,type,image);
    POST_USER_CALL(glConvolutionFilter2D,glConvolutionFilter2D(target,internalformat,width,height,format,type,image))
}

void GLAPIENTRY glConvolutionFilter2DEXT(GLenum _p0, GLenum _p1, GLsizei _p2, GLsizei _p3, GLenum _p4, GLenum _p5, const GLvoid *_p6)
{
    gli().init();
    PREV_USER_CALL(glConvolutionFilter2DEXT,glConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glConvolutionFilter2DEXT,glConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glConvolutionParameterf(GLenum target, GLenum pname, GLfloat params)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameterf,glConvolutionParameterf(target,pname,params))
    glCalls().glConvolutionParameterf(target,pname,params);
    POST_USER_CALL(glConvolutionParameterf,glConvolutionParameterf(target,pname,params))
}

void GLAPIENTRY glConvolutionParameterfEXT(GLenum _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameterfEXT,glConvolutionParameterfEXT(_p0,_p1,_p2))
    glCalls().glConvolutionParameterfEXT(_p0,_p1,_p2);
    POST_USER_CALL(glConvolutionParameterfEXT,glConvolutionParameterfEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glConvolutionParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameterfv,glConvolutionParameterfv(target,pname,params))
    glCalls().glConvolutionParameterfv(target,pname,params);
    POST_USER_CALL(glConvolutionParameterfv,glConvolutionParameterfv(target,pname,params))
}

void GLAPIENTRY glConvolutionParameterfvEXT(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameterfvEXT,glConvolutionParameterfvEXT(_p0,_p1,_p2))
    glCalls().glConvolutionParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glConvolutionParameterfvEXT,glConvolutionParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glConvolutionParameteri(GLenum target, GLenum pname, GLint params)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameteri,glConvolutionParameteri(target,pname,params))
    glCalls().glConvolutionParameteri(target,pname,params);
    POST_USER_CALL(glConvolutionParameteri,glConvolutionParameteri(target,pname,params))
}

void GLAPIENTRY glConvolutionParameteriEXT(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameteriEXT,glConvolutionParameteriEXT(_p0,_p1,_p2))
    glCalls().glConvolutionParameteriEXT(_p0,_p1,_p2);
    POST_USER_CALL(glConvolutionParameteriEXT,glConvolutionParameteriEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glConvolutionParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameteriv,glConvolutionParameteriv(target,pname,params))
    glCalls().glConvolutionParameteriv(target,pname,params);
    POST_USER_CALL(glConvolutionParameteriv,glConvolutionParameteriv(target,pname,params))
}

void GLAPIENTRY glConvolutionParameterivEXT(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glConvolutionParameterivEXT,glConvolutionParameterivEXT(_p0,_p1,_p2))
    glCalls().glConvolutionParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glConvolutionParameterivEXT,glConvolutionParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glCopyBufferSubData(GLenum _p0, GLenum _p1, GLintptr _p2, GLintptr _p3, GLsizeiptr _p4)
{
    gli().init();
    PREV_USER_CALL(glCopyBufferSubData,glCopyBufferSubData(_p0,_p1,_p2,_p3,_p4))
    glCalls().glCopyBufferSubData(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glCopyBufferSubData,glCopyBufferSubData(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glCopyColorSubTable(GLenum target, GLsizei start, GLint x, GLint y, GLsizei width)
{
    gli().init();
    PREV_USER_CALL(glCopyColorSubTable,glCopyColorSubTable(target,start,x,y,width))
    glCalls().glCopyColorSubTable(target,start,x,y,width);
    POST_USER_CALL(glCopyColorSubTable,glCopyColorSubTable(target,start,x,y,width))
}

void GLAPIENTRY glCopyColorSubTableEXT(GLenum _p0, GLsizei _p1, GLint _p2, GLint _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glCopyColorSubTableEXT,glCopyColorSubTableEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glCopyColorSubTableEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glCopyColorSubTableEXT,glCopyColorSubTableEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glCopyColorTable(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    gli().init();
    PREV_USER_CALL(glCopyColorTable,glCopyColorTable(target,internalformat,x,y,width))
    glCalls().glCopyColorTable(target,internalformat,x,y,width);
    POST_USER_CALL(glCopyColorTable,glCopyColorTable(target,internalformat,x,y,width))
}

void GLAPIENTRY glCopyColorTableSGI(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glCopyColorTableSGI,glCopyColorTableSGI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glCopyColorTableSGI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glCopyColorTableSGI,glCopyColorTableSGI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glCopyConvolutionFilter1D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width)
{
    gli().init();
    PREV_USER_CALL(glCopyConvolutionFilter1D,glCopyConvolutionFilter1D(target,internalformat,x,y,width))
    glCalls().glCopyConvolutionFilter1D(target,internalformat,x,y,width);
    POST_USER_CALL(glCopyConvolutionFilter1D,glCopyConvolutionFilter1D(target,internalformat,x,y,width))
}

void GLAPIENTRY glCopyConvolutionFilter1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glCopyConvolutionFilter1DEXT,glCopyConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glCopyConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glCopyConvolutionFilter1DEXT,glCopyConvolutionFilter1DEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glCopyConvolutionFilter2D(GLenum target, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height)
{
    gli().init();
    PREV_USER_CALL(glCopyConvolutionFilter2D,glCopyConvolutionFilter2D(target,internalformat,x,y,width,height))
    glCalls().glCopyConvolutionFilter2D(target,internalformat,x,y,width,height);
    POST_USER_CALL(glCopyConvolutionFilter2D,glCopyConvolutionFilter2D(target,internalformat,x,y,width,height))
}

void GLAPIENTRY glCopyConvolutionFilter2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4, GLsizei _p5)
{
    gli().init();
    PREV_USER_CALL(glCopyConvolutionFilter2DEXT,glCopyConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glCopyConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glCopyConvolutionFilter2DEXT,glCopyConvolutionFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glCopyMultiTexImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint _p4, GLint _p5, GLsizei _p6, GLint _p7)
{
    gli().init();
    PREV_USER_CALL(glCopyMultiTexImage1DEXT,glCopyMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCopyMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCopyMultiTexImage1DEXT,glCopyMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCopyMultiTexImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLint _p8)
{
    gli().init();
    PREV_USER_CALL(glCopyMultiTexImage2DEXT,glCopyMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCopyMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCopyMultiTexImage2DEXT,glCopyMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCopyMultiTexSubImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6)
{
    gli().init();
    PREV_USER_CALL(glCopyMultiTexSubImage1DEXT,glCopyMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glCopyMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glCopyMultiTexSubImage1DEXT,glCopyMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glCopyMultiTexSubImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLsizei _p7, GLsizei _p8)
{
    gli().init();
    PREV_USER_CALL(glCopyMultiTexSubImage2DEXT,glCopyMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCopyMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCopyMultiTexSubImage2DEXT,glCopyMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCopyMultiTexSubImage3DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLint _p7, GLsizei _p8, GLsizei _p9)
{
    gli().init();
    PREV_USER_CALL(glCopyMultiTexSubImage3DEXT,glCopyMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCopyMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCopyMultiTexSubImage3DEXT,glCopyMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glCopyPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum type)
{
    gli().init();
    PREV_USER_CALL(glCopyPixels,glCopyPixels(x,y,width,height,type))
    glCalls().glCopyPixels(x,y,width,height,type);
    POST_USER_CALL(glCopyPixels,glCopyPixels(x,y,width,height,type))
}

void GLAPIENTRY glCopyTexImage1D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLint border)
{
    gli().init();
    PREV_USER_CALL(glCopyTexImage1D,glCopyTexImage1D(target,level,internalformat,x,y,width,border))
    glCalls().glCopyTexImage1D(target,level,internalformat,x,y,width,border);
    POST_USER_CALL(glCopyTexImage1D,glCopyTexImage1D(target,level,internalformat,x,y,width,border))
}

void GLAPIENTRY glCopyTexImage1DEXT(GLenum _p0, GLint _p1, GLenum _p2, GLint _p3, GLint _p4, GLsizei _p5, GLint _p6)
{
    gli().init();
    PREV_USER_CALL(glCopyTexImage1DEXT,glCopyTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glCopyTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glCopyTexImage1DEXT,glCopyTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glCopyTexImage2D(GLenum target, GLint level, GLenum internalformat, GLint x, GLint y, GLsizei width, GLsizei height, GLint border)
{
    gli().init();
    PREV_USER_CALL(glCopyTexImage2D,glCopyTexImage2D(target,level,internalformat,x,y,width,height,border))
    glCalls().glCopyTexImage2D(target,level,internalformat,x,y,width,height,border);
    POST_USER_CALL(glCopyTexImage2D,glCopyTexImage2D(target,level,internalformat,x,y,width,height,border))
}

void GLAPIENTRY glCopyTexImage2DEXT(GLenum _p0, GLint _p1, GLenum _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLint _p7)
{
    gli().init();
    PREV_USER_CALL(glCopyTexImage2DEXT,glCopyTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCopyTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCopyTexImage2DEXT,glCopyTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCopyTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLint x, GLint y, GLsizei width)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage1D,glCopyTexSubImage1D(target,level,xoffset,x,y,width))
    glCalls().glCopyTexSubImage1D(target,level,xoffset,x,y,width);
    POST_USER_CALL(glCopyTexSubImage1D,glCopyTexSubImage1D(target,level,xoffset,x,y,width))
}

void GLAPIENTRY glCopyTexSubImage1DEXT(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage1DEXT,glCopyTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glCopyTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glCopyTexSubImage1DEXT,glCopyTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glCopyTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage2D,glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height))
    glCalls().glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height);
    POST_USER_CALL(glCopyTexSubImage2D,glCopyTexSubImage2D(target,level,xoffset,yoffset,x,y,width,height))
}

void GLAPIENTRY glCopyTexSubImage2DEXT(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage2DEXT,glCopyTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCopyTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCopyTexSubImage2DEXT,glCopyTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCopyTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLint x, GLint y, GLsizei width, GLsizei height)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage3D,glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height))
    glCalls().glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height);
    POST_USER_CALL(glCopyTexSubImage3D,glCopyTexSubImage3D(target,level,xoffset,yoffset,zoffset,x,y,width,height))
}

void GLAPIENTRY glCopyTexSubImage3DEXT(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLsizei _p7, GLsizei _p8)
{
    gli().init();
    PREV_USER_CALL(glCopyTexSubImage3DEXT,glCopyTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCopyTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCopyTexSubImage3DEXT,glCopyTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCopyTextureImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint _p4, GLint _p5, GLsizei _p6, GLint _p7)
{
    gli().init();
    PREV_USER_CALL(glCopyTextureImage1DEXT,glCopyTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glCopyTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glCopyTextureImage1DEXT,glCopyTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glCopyTextureImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLint _p8)
{
    gli().init();
    PREV_USER_CALL(glCopyTextureImage2DEXT,glCopyTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCopyTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCopyTextureImage2DEXT,glCopyTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCopyTextureSubImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6)
{
    gli().init();
    PREV_USER_CALL(glCopyTextureSubImage1DEXT,glCopyTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glCopyTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glCopyTextureSubImage1DEXT,glCopyTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glCopyTextureSubImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLsizei _p7, GLsizei _p8)
{
    gli().init();
    PREV_USER_CALL(glCopyTextureSubImage2DEXT,glCopyTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glCopyTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glCopyTextureSubImage2DEXT,glCopyTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glCopyTextureSubImage3DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6, GLint _p7, GLsizei _p8, GLsizei _p9)
{
    gli().init();
    PREV_USER_CALL(glCopyTextureSubImage3DEXT,glCopyTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glCopyTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glCopyTextureSubImage3DEXT,glCopyTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

GLuint GLAPIENTRY glCreateProgram()
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glCreateProgram,glCreateProgram())
    _result = glCalls().glCreateProgram();
    POST_USER_CALL(glCreateProgram,glCreateProgram())
    return _result;
}

GLhandleARB GLAPIENTRY glCreateProgramObjectARB()
{
    gli().init();
    GLhandleARB _result;
    PREV_USER_CALL(glCreateProgramObjectARB,glCreateProgramObjectARB())
    _result = glCalls().glCreateProgramObjectARB();
    POST_USER_CALL(glCreateProgramObjectARB,glCreateProgramObjectARB())
    return _result;
}

GLuint GLAPIENTRY glCreateShader(GLenum _p0)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glCreateShader,glCreateShader(_p0))
    _result = glCalls().glCreateShader(_p0);
    POST_USER_CALL(glCreateShader,glCreateShader(_p0))
    return _result;
}

GLhandleARB GLAPIENTRY glCreateShaderObjectARB(GLenum _p0)
{
    gli().init();
    GLhandleARB _result;
    PREV_USER_CALL(glCreateShaderObjectARB,glCreateShaderObjectARB(_p0))
    _result = glCalls().glCreateShaderObjectARB(_p0);
    POST_USER_CALL(glCreateShaderObjectARB,glCreateShaderObjectARB(_p0))
    return _result;
}

void GLAPIENTRY glCullFace(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glCullFace,glCullFace(mode))
    glCalls().glCullFace(mode);
    POST_USER_CALL(glCullFace,glCullFace(mode))
}

void GLAPIENTRY glCullParameterdvEXT(GLenum _p0, GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glCullParameterdvEXT,glCullParameterdvEXT(_p0,_p1))
    glCalls().glCullParameterdvEXT(_p0,_p1);
    POST_USER_CALL(glCullParameterdvEXT,glCullParameterdvEXT(_p0,_p1))
}

void GLAPIENTRY glCullParameterfvEXT(GLenum _p0, GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glCullParameterfvEXT,glCullParameterfvEXT(_p0,_p1))
    glCalls().glCullParameterfvEXT(_p0,_p1);
    POST_USER_CALL(glCullParameterfvEXT,glCullParameterfvEXT(_p0,_p1))
}

void GLAPIENTRY glCurrentPaletteMatrixARB(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glCurrentPaletteMatrixARB,glCurrentPaletteMatrixARB(_p0))
    glCalls().glCurrentPaletteMatrixARB(_p0);
    POST_USER_CALL(glCurrentPaletteMatrixARB,glCurrentPaletteMatrixARB(_p0))
}

void GLAPIENTRY glDeformSGIX(GLbitfield _p0)
{
    gli().init();
    PREV_USER_CALL(glDeformSGIX,glDeformSGIX(_p0))
    glCalls().glDeformSGIX(_p0);
    POST_USER_CALL(glDeformSGIX,glDeformSGIX(_p0))
}

void GLAPIENTRY glDeformationMap3dSGIX(GLenum _p0, GLdouble _p1, GLdouble _p2, GLint _p3, GLint _p4, GLdouble _p5, GLdouble _p6, GLint _p7, GLint _p8, GLdouble _p9, GLdouble _p10, GLint _p11, GLint _p12, const GLdouble *_p13)
{
    gli().init();
    PREV_USER_CALL(glDeformationMap3dSGIX,glDeformationMap3dSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13))
    glCalls().glDeformationMap3dSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13);
    POST_USER_CALL(glDeformationMap3dSGIX,glDeformationMap3dSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13))
}

void GLAPIENTRY glDeformationMap3fSGIX(GLenum _p0, GLfloat _p1, GLfloat _p2, GLint _p3, GLint _p4, GLfloat _p5, GLfloat _p6, GLint _p7, GLint _p8, GLfloat _p9, GLfloat _p10, GLint _p11, GLint _p12, const GLfloat *_p13)
{
    gli().init();
    PREV_USER_CALL(glDeformationMap3fSGIX,glDeformationMap3fSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13))
    glCalls().glDeformationMap3fSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13);
    POST_USER_CALL(glDeformationMap3fSGIX,glDeformationMap3fSGIX(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12,_p13))
}

void GLAPIENTRY glDeleteAsyncMarkersSGIX(GLuint _p0, GLsizei _p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteAsyncMarkersSGIX,glDeleteAsyncMarkersSGIX(_p0,_p1))
    glCalls().glDeleteAsyncMarkersSGIX(_p0,_p1);
    POST_USER_CALL(glDeleteAsyncMarkersSGIX,glDeleteAsyncMarkersSGIX(_p0,_p1))
}

void GLAPIENTRY glDeleteBuffers(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteBuffers,glDeleteBuffers(_p0,_p1))
    glCalls().glDeleteBuffers(_p0,_p1);
    POST_USER_CALL(glDeleteBuffers,glDeleteBuffers(_p0,_p1))
}

void GLAPIENTRY glDeleteBuffersARB(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteBuffersARB,glDeleteBuffersARB(_p0,_p1))
    glCalls().glDeleteBuffersARB(_p0,_p1);
    POST_USER_CALL(glDeleteBuffersARB,glDeleteBuffersARB(_p0,_p1))
}

void GLAPIENTRY glDeleteFencesAPPLE(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteFencesAPPLE,glDeleteFencesAPPLE(_p0,_p1))
    glCalls().glDeleteFencesAPPLE(_p0,_p1);
    POST_USER_CALL(glDeleteFencesAPPLE,glDeleteFencesAPPLE(_p0,_p1))
}

void GLAPIENTRY glDeleteFencesNV(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteFencesNV,glDeleteFencesNV(_p0,_p1))
    glCalls().glDeleteFencesNV(_p0,_p1);
    POST_USER_CALL(glDeleteFencesNV,glDeleteFencesNV(_p0,_p1))
}

void GLAPIENTRY glDeleteFragmentShaderATI(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteFragmentShaderATI,glDeleteFragmentShaderATI(_p0))
    glCalls().glDeleteFragmentShaderATI(_p0);
    POST_USER_CALL(glDeleteFragmentShaderATI,glDeleteFragmentShaderATI(_p0))
}

void GLAPIENTRY glDeleteFramebuffers(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteFramebuffers,glDeleteFramebuffers(_p0,_p1))
    glCalls().glDeleteFramebuffers(_p0,_p1);
    POST_USER_CALL(glDeleteFramebuffers,glDeleteFramebuffers(_p0,_p1))
}

void GLAPIENTRY glDeleteFramebuffersEXT(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteFramebuffersEXT,glDeleteFramebuffersEXT(_p0,_p1))
    glCalls().glDeleteFramebuffersEXT(_p0,_p1);
    POST_USER_CALL(glDeleteFramebuffersEXT,glDeleteFramebuffersEXT(_p0,_p1))
}

void GLAPIENTRY glDeleteLists(GLuint list, GLsizei range)
{
    gli().init();
    PREV_USER_CALL(glDeleteLists,glDeleteLists(list,range))
    glCalls().glDeleteLists(list,range);
    POST_USER_CALL(glDeleteLists,glDeleteLists(list,range))
}

void GLAPIENTRY glDeleteObjectARB(GLhandleARB _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteObjectARB,glDeleteObjectARB(_p0))
    glCalls().glDeleteObjectARB(_p0);
    POST_USER_CALL(glDeleteObjectARB,glDeleteObjectARB(_p0))
}

void GLAPIENTRY glDeleteObjectBufferATI(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteObjectBufferATI,glDeleteObjectBufferATI(_p0))
    glCalls().glDeleteObjectBufferATI(_p0);
    POST_USER_CALL(glDeleteObjectBufferATI,glDeleteObjectBufferATI(_p0))
}

void GLAPIENTRY glDeleteOcclusionQueriesNV(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteOcclusionQueriesNV,glDeleteOcclusionQueriesNV(_p0,_p1))
    glCalls().glDeleteOcclusionQueriesNV(_p0,_p1);
    POST_USER_CALL(glDeleteOcclusionQueriesNV,glDeleteOcclusionQueriesNV(_p0,_p1))
}

void GLAPIENTRY glDeletePerfMonitorsAMD(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeletePerfMonitorsAMD,glDeletePerfMonitorsAMD(_p0,_p1))
    glCalls().glDeletePerfMonitorsAMD(_p0,_p1);
    POST_USER_CALL(glDeletePerfMonitorsAMD,glDeletePerfMonitorsAMD(_p0,_p1))
}

void GLAPIENTRY glDeleteProgram(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteProgram,glDeleteProgram(_p0))
    glCalls().glDeleteProgram(_p0);
    POST_USER_CALL(glDeleteProgram,glDeleteProgram(_p0))
}

void GLAPIENTRY glDeleteProgramsARB(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteProgramsARB,glDeleteProgramsARB(_p0,_p1))
    glCalls().glDeleteProgramsARB(_p0,_p1);
    POST_USER_CALL(glDeleteProgramsARB,glDeleteProgramsARB(_p0,_p1))
}

void GLAPIENTRY glDeleteProgramsNV(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteProgramsNV,glDeleteProgramsNV(_p0,_p1))
    glCalls().glDeleteProgramsNV(_p0,_p1);
    POST_USER_CALL(glDeleteProgramsNV,glDeleteProgramsNV(_p0,_p1))
}

void GLAPIENTRY glDeleteQueries(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteQueries,glDeleteQueries(_p0,_p1))
    glCalls().glDeleteQueries(_p0,_p1);
    POST_USER_CALL(glDeleteQueries,glDeleteQueries(_p0,_p1))
}

void GLAPIENTRY glDeleteQueriesARB(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteQueriesARB,glDeleteQueriesARB(_p0,_p1))
    glCalls().glDeleteQueriesARB(_p0,_p1);
    POST_USER_CALL(glDeleteQueriesARB,glDeleteQueriesARB(_p0,_p1))
}

void GLAPIENTRY glDeleteRenderbuffers(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteRenderbuffers,glDeleteRenderbuffers(_p0,_p1))
    glCalls().glDeleteRenderbuffers(_p0,_p1);
    POST_USER_CALL(glDeleteRenderbuffers,glDeleteRenderbuffers(_p0,_p1))
}

void GLAPIENTRY glDeleteRenderbuffersEXT(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteRenderbuffersEXT,glDeleteRenderbuffersEXT(_p0,_p1))
    glCalls().glDeleteRenderbuffersEXT(_p0,_p1);
    POST_USER_CALL(glDeleteRenderbuffersEXT,glDeleteRenderbuffersEXT(_p0,_p1))
}

void GLAPIENTRY glDeleteShader(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteShader,glDeleteShader(_p0))
    glCalls().glDeleteShader(_p0);
    POST_USER_CALL(glDeleteShader,glDeleteShader(_p0))
}

void GLAPIENTRY glDeleteTextures(GLsizei n, const GLuint *textures)
{
    gli().init();
    PREV_USER_CALL(glDeleteTextures,glDeleteTextures(n,textures))
    glCalls().glDeleteTextures(n,textures);
    POST_USER_CALL(glDeleteTextures,glDeleteTextures(n,textures))
}

void GLAPIENTRY glDeleteTexturesEXT(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteTexturesEXT,glDeleteTexturesEXT(_p0,_p1))
    glCalls().glDeleteTexturesEXT(_p0,_p1);
    POST_USER_CALL(glDeleteTexturesEXT,glDeleteTexturesEXT(_p0,_p1))
}

void GLAPIENTRY glDeleteTransformFeedbacksNV(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteTransformFeedbacksNV,glDeleteTransformFeedbacksNV(_p0,_p1))
    glCalls().glDeleteTransformFeedbacksNV(_p0,_p1);
    POST_USER_CALL(glDeleteTransformFeedbacksNV,glDeleteTransformFeedbacksNV(_p0,_p1))
}

void GLAPIENTRY glDeleteVertexArrays(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteVertexArrays,glDeleteVertexArrays(_p0,_p1))
    glCalls().glDeleteVertexArrays(_p0,_p1);
    POST_USER_CALL(glDeleteVertexArrays,glDeleteVertexArrays(_p0,_p1))
}

void GLAPIENTRY glDeleteVertexArraysAPPLE(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glDeleteVertexArraysAPPLE,glDeleteVertexArraysAPPLE(_p0,_p1))
    glCalls().glDeleteVertexArraysAPPLE(_p0,_p1);
    POST_USER_CALL(glDeleteVertexArraysAPPLE,glDeleteVertexArraysAPPLE(_p0,_p1))
}

void GLAPIENTRY glDeleteVertexShaderEXT(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDeleteVertexShaderEXT,glDeleteVertexShaderEXT(_p0))
    glCalls().glDeleteVertexShaderEXT(_p0);
    POST_USER_CALL(glDeleteVertexShaderEXT,glDeleteVertexShaderEXT(_p0))
}

void GLAPIENTRY glDepthBoundsEXT(GLclampd _p0, GLclampd _p1)
{
    gli().init();
    PREV_USER_CALL(glDepthBoundsEXT,glDepthBoundsEXT(_p0,_p1))
    glCalls().glDepthBoundsEXT(_p0,_p1);
    POST_USER_CALL(glDepthBoundsEXT,glDepthBoundsEXT(_p0,_p1))
}

void GLAPIENTRY glDepthBoundsdNV(GLdouble _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glDepthBoundsdNV,glDepthBoundsdNV(_p0,_p1))
    glCalls().glDepthBoundsdNV(_p0,_p1);
    POST_USER_CALL(glDepthBoundsdNV,glDepthBoundsdNV(_p0,_p1))
}

void GLAPIENTRY glDepthFunc(GLenum func)
{
    gli().init();
    PREV_USER_CALL(glDepthFunc,glDepthFunc(func))
    glCalls().glDepthFunc(func);
    POST_USER_CALL(glDepthFunc,glDepthFunc(func))
}

void GLAPIENTRY glDepthMask(GLboolean flag)
{
    gli().init();
    PREV_USER_CALL(glDepthMask,glDepthMask(flag))
    glCalls().glDepthMask(flag);
    POST_USER_CALL(glDepthMask,glDepthMask(flag))
}

void GLAPIENTRY glDepthRange(GLclampd near_val, GLclampd far_val)
{
    gli().init();
    PREV_USER_CALL(glDepthRange,glDepthRange(near_val,far_val))
    glCalls().glDepthRange(near_val,far_val);
    POST_USER_CALL(glDepthRange,glDepthRange(near_val,far_val))
}

void GLAPIENTRY glDepthRangedNV(GLdouble _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glDepthRangedNV,glDepthRangedNV(_p0,_p1))
    glCalls().glDepthRangedNV(_p0,_p1);
    POST_USER_CALL(glDepthRangedNV,glDepthRangedNV(_p0,_p1))
}

void GLAPIENTRY glDetachObjectARB(GLhandleARB _p0, GLhandleARB _p1)
{
    gli().init();
    PREV_USER_CALL(glDetachObjectARB,glDetachObjectARB(_p0,_p1))
    glCalls().glDetachObjectARB(_p0,_p1);
    POST_USER_CALL(glDetachObjectARB,glDetachObjectARB(_p0,_p1))
}

void GLAPIENTRY glDetachShader(GLuint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glDetachShader,glDetachShader(_p0,_p1))
    glCalls().glDetachShader(_p0,_p1);
    POST_USER_CALL(glDetachShader,glDetachShader(_p0,_p1))
}

void GLAPIENTRY glDetailTexFuncSGIS(GLenum _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glDetailTexFuncSGIS,glDetailTexFuncSGIS(_p0,_p1,_p2))
    glCalls().glDetailTexFuncSGIS(_p0,_p1,_p2);
    POST_USER_CALL(glDetailTexFuncSGIS,glDetailTexFuncSGIS(_p0,_p1,_p2))
}

void GLAPIENTRY glDisable(GLenum cap)
{
    gli().init();
    PREV_USER_CALL(glDisable,glDisable(cap))
    glCalls().glDisable(cap);
    POST_USER_CALL(glDisable,glDisable(cap))
}

void GLAPIENTRY glDisableClientState(GLenum cap)
{
    gli().init();
    PREV_USER_CALL(glDisableClientState,glDisableClientState(cap))
    glCalls().glDisableClientState(cap);
    POST_USER_CALL(glDisableClientState,glDisableClientState(cap))
}

void GLAPIENTRY glDisableClientStateIndexedEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glDisableClientStateIndexedEXT,glDisableClientStateIndexedEXT(_p0,_p1))
    glCalls().glDisableClientStateIndexedEXT(_p0,_p1);
    POST_USER_CALL(glDisableClientStateIndexedEXT,glDisableClientStateIndexedEXT(_p0,_p1))
}

void GLAPIENTRY glDisableIndexedEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glDisableIndexedEXT,glDisableIndexedEXT(_p0,_p1))
    glCalls().glDisableIndexedEXT(_p0,_p1);
    POST_USER_CALL(glDisableIndexedEXT,glDisableIndexedEXT(_p0,_p1))
}

void GLAPIENTRY glDisableVariantClientStateEXT(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDisableVariantClientStateEXT,glDisableVariantClientStateEXT(_p0))
    glCalls().glDisableVariantClientStateEXT(_p0);
    POST_USER_CALL(glDisableVariantClientStateEXT,glDisableVariantClientStateEXT(_p0))
}

void GLAPIENTRY glDisableVertexAttribArray(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDisableVertexAttribArray,glDisableVertexAttribArray(_p0))
    glCalls().glDisableVertexAttribArray(_p0);
    POST_USER_CALL(glDisableVertexAttribArray,glDisableVertexAttribArray(_p0))
}

void GLAPIENTRY glDisableVertexAttribArrayARB(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glDisableVertexAttribArrayARB,glDisableVertexAttribArrayARB(_p0))
    glCalls().glDisableVertexAttribArrayARB(_p0);
    POST_USER_CALL(glDisableVertexAttribArrayARB,glDisableVertexAttribArrayARB(_p0))
}

void GLAPIENTRY glDisablei(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glDisablei,glDisablei(_p0,_p1))
    glCalls().glDisablei(_p0,_p1);
    POST_USER_CALL(glDisablei,glDisablei(_p0,_p1))
}

void GLAPIENTRY glDrawArrays(GLenum mode, GLint first, GLsizei count)
{
    gli().init();
    PREV_USER_CALL(glDrawArrays,glDrawArrays(mode,first,count))
    glCalls().glDrawArrays(mode,first,count);
    gli().incVertexCount(count-first);
    POST_USER_CALL(glDrawArrays,glDrawArrays(mode,first,count))
    gli().doEndBatchEvent();
}

void GLAPIENTRY glDrawArraysEXT(GLenum _p0, GLint _p1, GLsizei _p2)
{
    gli().init();
    PREV_USER_CALL(glDrawArraysEXT,glDrawArraysEXT(_p0,_p1,_p2))
    glCalls().glDrawArraysEXT(_p0,_p1,_p2);
    POST_USER_CALL(glDrawArraysEXT,glDrawArraysEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glDrawArraysInstanced(GLenum _p0, GLint _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glDrawArraysInstanced,glDrawArraysInstanced(_p0,_p1,_p2,_p3))
    glCalls().glDrawArraysInstanced(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glDrawArraysInstanced,glDrawArraysInstanced(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glDrawArraysInstancedARB(GLenum _p0, GLint _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glDrawArraysInstancedARB,glDrawArraysInstancedARB(_p0,_p1,_p2,_p3))
    glCalls().glDrawArraysInstancedARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glDrawArraysInstancedARB,glDrawArraysInstancedARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glDrawArraysInstancedEXT(GLenum _p0, GLint _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glDrawArraysInstancedEXT,glDrawArraysInstancedEXT(_p0,_p1,_p2,_p3))
    glCalls().glDrawArraysInstancedEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glDrawArraysInstancedEXT,glDrawArraysInstancedEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glDrawBuffer(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glDrawBuffer,glDrawBuffer(mode))
    glCalls().glDrawBuffer(mode);
    POST_USER_CALL(glDrawBuffer,glDrawBuffer(mode))
}

void GLAPIENTRY glDrawBuffers(GLsizei _p0, const GLenum *_p1)
{
    gli().init();
    PREV_USER_CALL(glDrawBuffers,glDrawBuffers(_p0,_p1))
    glCalls().glDrawBuffers(_p0,_p1);
    POST_USER_CALL(glDrawBuffers,glDrawBuffers(_p0,_p1))
}

void GLAPIENTRY glDrawBuffersARB(GLsizei _p0, const GLenum *_p1)
{
    gli().init();
    PREV_USER_CALL(glDrawBuffersARB,glDrawBuffersARB(_p0,_p1))
    glCalls().glDrawBuffersARB(_p0,_p1);
    POST_USER_CALL(glDrawBuffersARB,glDrawBuffersARB(_p0,_p1))
}

void GLAPIENTRY glDrawBuffersATI(GLsizei _p0, const GLenum *_p1)
{
    gli().init();
    PREV_USER_CALL(glDrawBuffersATI,glDrawBuffersATI(_p0,_p1))
    glCalls().glDrawBuffersATI(_p0,_p1);
    POST_USER_CALL(glDrawBuffersATI,glDrawBuffersATI(_p0,_p1))
}

void GLAPIENTRY glDrawElementArrayAPPLE(GLenum _p0, GLint _p1, GLsizei _p2)
{
    gli().init();
    PREV_USER_CALL(glDrawElementArrayAPPLE,glDrawElementArrayAPPLE(_p0,_p1,_p2))
    glCalls().glDrawElementArrayAPPLE(_p0,_p1,_p2);
    POST_USER_CALL(glDrawElementArrayAPPLE,glDrawElementArrayAPPLE(_p0,_p1,_p2))
}

void GLAPIENTRY glDrawElementArrayATI(GLenum _p0, GLsizei _p1)
{
    gli().init();
    PREV_USER_CALL(glDrawElementArrayATI,glDrawElementArrayATI(_p0,_p1))
    glCalls().glDrawElementArrayATI(_p0,_p1);
    POST_USER_CALL(glDrawElementArrayATI,glDrawElementArrayATI(_p0,_p1))
}

void GLAPIENTRY glDrawElements(GLenum mode, GLsizei count, GLenum type, const GLvoid *indices)
{
    gli().init();
    PREV_USER_CALL(glDrawElements,glDrawElements(mode,count,type,indices))
    glCalls().glDrawElements(mode,count,type,indices);
    gli().incVertexCount(count);
    POST_USER_CALL(glDrawElements,glDrawElements(mode,count,type,indices))
    gli().doEndBatchEvent();
}

void GLAPIENTRY glDrawElementsInstanced(GLenum _p0, GLsizei _p1, GLenum _p2, const GLvoid *_p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glDrawElementsInstanced,glDrawElementsInstanced(_p0,_p1,_p2,_p3,_p4))
    glCalls().glDrawElementsInstanced(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glDrawElementsInstanced,glDrawElementsInstanced(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glDrawElementsInstancedARB(GLenum _p0, GLsizei _p1, GLenum _p2, const GLvoid *_p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glDrawElementsInstancedARB,glDrawElementsInstancedARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glDrawElementsInstancedARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glDrawElementsInstancedARB,glDrawElementsInstancedARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glDrawElementsInstancedEXT(GLenum _p0, GLsizei _p1, GLenum _p2, const GLvoid *_p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glDrawElementsInstancedEXT,glDrawElementsInstancedEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glDrawElementsInstancedEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glDrawElementsInstancedEXT,glDrawElementsInstancedEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glDrawPixels(GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glDrawPixels,glDrawPixels(width,height,format,type,pixels))
    glCalls().glDrawPixels(width,height,format,type,pixels);
    POST_USER_CALL(glDrawPixels,glDrawPixels(width,height,format,type,pixels))
}

void GLAPIENTRY glDrawRangeElementArrayAPPLE(GLenum _p0, GLuint _p1, GLuint _p2, GLint _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glDrawRangeElementArrayAPPLE,glDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4))
    glCalls().glDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glDrawRangeElementArrayAPPLE,glDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glDrawRangeElementArrayATI(GLenum _p0, GLuint _p1, GLuint _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glDrawRangeElementArrayATI,glDrawRangeElementArrayATI(_p0,_p1,_p2,_p3))
    glCalls().glDrawRangeElementArrayATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glDrawRangeElementArrayATI,glDrawRangeElementArrayATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glDrawRangeElements(GLenum mode, GLuint start, GLuint end, GLsizei count, GLenum type, const GLvoid *indices)
{
    gli().init();
    PREV_USER_CALL(glDrawRangeElements,glDrawRangeElements(mode,start,end,count,type,indices))
    glCalls().glDrawRangeElements(mode,start,end,count,type,indices);
    gli().incVertexCount(count);
    POST_USER_CALL(glDrawRangeElements,glDrawRangeElements(mode,start,end,count,type,indices))
    gli().doEndBatchEvent();
}

void GLAPIENTRY glDrawRangeElementsEXT(GLenum _p0, GLuint _p1, GLuint _p2, GLsizei _p3, GLenum _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glDrawRangeElementsEXT,glDrawRangeElementsEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glDrawRangeElementsEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glDrawRangeElementsEXT,glDrawRangeElementsEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glDrawTransformFeedbackNV(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glDrawTransformFeedbackNV,glDrawTransformFeedbackNV(_p0,_p1))
    glCalls().glDrawTransformFeedbackNV(_p0,_p1);
    POST_USER_CALL(glDrawTransformFeedbackNV,glDrawTransformFeedbackNV(_p0,_p1))
}

void GLAPIENTRY glEdgeFlag(GLboolean flag)
{
    gli().init();
    PREV_USER_CALL(glEdgeFlag,glEdgeFlag(flag))
    glCalls().glEdgeFlag(flag);
    POST_USER_CALL(glEdgeFlag,glEdgeFlag(flag))
}

void GLAPIENTRY glEdgeFlagPointer(GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glEdgeFlagPointer,glEdgeFlagPointer(stride,ptr))
    glCalls().glEdgeFlagPointer(stride,ptr);
    POST_USER_CALL(glEdgeFlagPointer,glEdgeFlagPointer(stride,ptr))
}

void GLAPIENTRY glEdgeFlagPointerEXT(GLsizei _p0, GLsizei _p1, const GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glEdgeFlagPointerEXT,glEdgeFlagPointerEXT(_p0,_p1,_p2))
    glCalls().glEdgeFlagPointerEXT(_p0,_p1,_p2);
    POST_USER_CALL(glEdgeFlagPointerEXT,glEdgeFlagPointerEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glEdgeFlagv(const GLboolean *flag)
{
    gli().init();
    PREV_USER_CALL(glEdgeFlagv,glEdgeFlagv(flag))
    glCalls().glEdgeFlagv(flag);
    POST_USER_CALL(glEdgeFlagv,glEdgeFlagv(flag))
}

void GLAPIENTRY glElementPointerAPPLE(GLenum _p0, const GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glElementPointerAPPLE,glElementPointerAPPLE(_p0,_p1))
    glCalls().glElementPointerAPPLE(_p0,_p1);
    POST_USER_CALL(glElementPointerAPPLE,glElementPointerAPPLE(_p0,_p1))
}

void GLAPIENTRY glElementPointerATI(GLenum _p0, const GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glElementPointerATI,glElementPointerATI(_p0,_p1))
    glCalls().glElementPointerATI(_p0,_p1);
    POST_USER_CALL(glElementPointerATI,glElementPointerATI(_p0,_p1))
}

void GLAPIENTRY glEnable(GLenum cap)
{
    gli().init();
    PREV_USER_CALL(glEnable,glEnable(cap))
    glCalls().glEnable(cap);
    POST_USER_CALL(glEnable,glEnable(cap))
}

void GLAPIENTRY glEnableClientState(GLenum cap)
{
    gli().init();
    PREV_USER_CALL(glEnableClientState,glEnableClientState(cap))
    glCalls().glEnableClientState(cap);
    POST_USER_CALL(glEnableClientState,glEnableClientState(cap))
}

void GLAPIENTRY glEnableClientStateIndexedEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glEnableClientStateIndexedEXT,glEnableClientStateIndexedEXT(_p0,_p1))
    glCalls().glEnableClientStateIndexedEXT(_p0,_p1);
    POST_USER_CALL(glEnableClientStateIndexedEXT,glEnableClientStateIndexedEXT(_p0,_p1))
}

void GLAPIENTRY glEnableIndexedEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glEnableIndexedEXT,glEnableIndexedEXT(_p0,_p1))
    glCalls().glEnableIndexedEXT(_p0,_p1);
    POST_USER_CALL(glEnableIndexedEXT,glEnableIndexedEXT(_p0,_p1))
}

void GLAPIENTRY glEnableVariantClientStateEXT(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glEnableVariantClientStateEXT,glEnableVariantClientStateEXT(_p0))
    glCalls().glEnableVariantClientStateEXT(_p0);
    POST_USER_CALL(glEnableVariantClientStateEXT,glEnableVariantClientStateEXT(_p0))
}

void GLAPIENTRY glEnableVertexAttribArray(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glEnableVertexAttribArray,glEnableVertexAttribArray(_p0))
    glCalls().glEnableVertexAttribArray(_p0);
    POST_USER_CALL(glEnableVertexAttribArray,glEnableVertexAttribArray(_p0))
}

void GLAPIENTRY glEnableVertexAttribArrayARB(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glEnableVertexAttribArrayARB,glEnableVertexAttribArrayARB(_p0))
    glCalls().glEnableVertexAttribArrayARB(_p0);
    POST_USER_CALL(glEnableVertexAttribArrayARB,glEnableVertexAttribArrayARB(_p0))
}

void GLAPIENTRY glEnablei(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glEnablei,glEnablei(_p0,_p1))
    glCalls().glEnablei(_p0,_p1);
    POST_USER_CALL(glEnablei,glEnablei(_p0,_p1))
}

void GLAPIENTRY glEnd()
{
    gli().init();
    PREV_USER_CALL(glEnd,glEnd())
    glCalls().glEnd();
    POST_USER_CALL(glEnd,glEnd())
    gli().doEndBatchEvent();
}

void GLAPIENTRY glEndConditionalRender()
{
    gli().init();
    PREV_USER_CALL(glEndConditionalRender,glEndConditionalRender())
    glCalls().glEndConditionalRender();
    POST_USER_CALL(glEndConditionalRender,glEndConditionalRender())
}

void GLAPIENTRY glEndConditionalRenderNV()
{
    gli().init();
    PREV_USER_CALL(glEndConditionalRenderNV,glEndConditionalRenderNV())
    glCalls().glEndConditionalRenderNV();
    POST_USER_CALL(glEndConditionalRenderNV,glEndConditionalRenderNV())
}

void GLAPIENTRY glEndFragmentShaderATI()
{
    gli().init();
    PREV_USER_CALL(glEndFragmentShaderATI,glEndFragmentShaderATI())
    glCalls().glEndFragmentShaderATI();
    POST_USER_CALL(glEndFragmentShaderATI,glEndFragmentShaderATI())
}

void GLAPIENTRY glEndList()
{
    gli().init();
    PREV_USER_CALL(glEndList,glEndList())
    glCalls().glEndList();
    POST_USER_CALL(glEndList,glEndList())
}

void GLAPIENTRY glEndOcclusionQueryNV()
{
    gli().init();
    PREV_USER_CALL(glEndOcclusionQueryNV,glEndOcclusionQueryNV())
    glCalls().glEndOcclusionQueryNV();
    POST_USER_CALL(glEndOcclusionQueryNV,glEndOcclusionQueryNV())
}

void GLAPIENTRY glEndPerfMonitorAMD(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glEndPerfMonitorAMD,glEndPerfMonitorAMD(_p0))
    glCalls().glEndPerfMonitorAMD(_p0);
    POST_USER_CALL(glEndPerfMonitorAMD,glEndPerfMonitorAMD(_p0))
}

void GLAPIENTRY glEndQuery(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glEndQuery,glEndQuery(_p0))
    glCalls().glEndQuery(_p0);
    POST_USER_CALL(glEndQuery,glEndQuery(_p0))
}

void GLAPIENTRY glEndQueryARB(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glEndQueryARB,glEndQueryARB(_p0))
    glCalls().glEndQueryARB(_p0);
    POST_USER_CALL(glEndQueryARB,glEndQueryARB(_p0))
}

void GLAPIENTRY glEndTransformFeedback()
{
    gli().init();
    PREV_USER_CALL(glEndTransformFeedback,glEndTransformFeedback())
    glCalls().glEndTransformFeedback();
    POST_USER_CALL(glEndTransformFeedback,glEndTransformFeedback())
}

void GLAPIENTRY glEndTransformFeedbackEXT()
{
    gli().init();
    PREV_USER_CALL(glEndTransformFeedbackEXT,glEndTransformFeedbackEXT())
    glCalls().glEndTransformFeedbackEXT();
    POST_USER_CALL(glEndTransformFeedbackEXT,glEndTransformFeedbackEXT())
}

void GLAPIENTRY glEndTransformFeedbackNV()
{
    gli().init();
    PREV_USER_CALL(glEndTransformFeedbackNV,glEndTransformFeedbackNV())
    glCalls().glEndTransformFeedbackNV();
    POST_USER_CALL(glEndTransformFeedbackNV,glEndTransformFeedbackNV())
}

void GLAPIENTRY glEndVertexShaderEXT()
{
    gli().init();
    PREV_USER_CALL(glEndVertexShaderEXT,glEndVertexShaderEXT())
    glCalls().glEndVertexShaderEXT();
    POST_USER_CALL(glEndVertexShaderEXT,glEndVertexShaderEXT())
}

void GLAPIENTRY glEvalCoord1d(GLdouble u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord1d,glEvalCoord1d(u))
    glCalls().glEvalCoord1d(u);
    POST_USER_CALL(glEvalCoord1d,glEvalCoord1d(u))
}

void GLAPIENTRY glEvalCoord1dv(const GLdouble *u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord1dv,glEvalCoord1dv(u))
    glCalls().glEvalCoord1dv(u);
    POST_USER_CALL(glEvalCoord1dv,glEvalCoord1dv(u))
}

void GLAPIENTRY glEvalCoord1f(GLfloat u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord1f,glEvalCoord1f(u))
    glCalls().glEvalCoord1f(u);
    POST_USER_CALL(glEvalCoord1f,glEvalCoord1f(u))
}

void GLAPIENTRY glEvalCoord1fv(const GLfloat *u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord1fv,glEvalCoord1fv(u))
    glCalls().glEvalCoord1fv(u);
    POST_USER_CALL(glEvalCoord1fv,glEvalCoord1fv(u))
}

void GLAPIENTRY glEvalCoord2d(GLdouble u, GLdouble v)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord2d,glEvalCoord2d(u,v))
    glCalls().glEvalCoord2d(u,v);
    POST_USER_CALL(glEvalCoord2d,glEvalCoord2d(u,v))
}

void GLAPIENTRY glEvalCoord2dv(const GLdouble *u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord2dv,glEvalCoord2dv(u))
    glCalls().glEvalCoord2dv(u);
    POST_USER_CALL(glEvalCoord2dv,glEvalCoord2dv(u))
}

void GLAPIENTRY glEvalCoord2f(GLfloat u, GLfloat v)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord2f,glEvalCoord2f(u,v))
    glCalls().glEvalCoord2f(u,v);
    POST_USER_CALL(glEvalCoord2f,glEvalCoord2f(u,v))
}

void GLAPIENTRY glEvalCoord2fv(const GLfloat *u)
{
    gli().init();
    PREV_USER_CALL(glEvalCoord2fv,glEvalCoord2fv(u))
    glCalls().glEvalCoord2fv(u);
    POST_USER_CALL(glEvalCoord2fv,glEvalCoord2fv(u))
}

void GLAPIENTRY glEvalMapsNV(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glEvalMapsNV,glEvalMapsNV(_p0,_p1))
    glCalls().glEvalMapsNV(_p0,_p1);
    POST_USER_CALL(glEvalMapsNV,glEvalMapsNV(_p0,_p1))
}

void GLAPIENTRY glEvalMesh1(GLenum mode, GLint i1, GLint i2)
{
    gli().init();
    PREV_USER_CALL(glEvalMesh1,glEvalMesh1(mode,i1,i2))
    glCalls().glEvalMesh1(mode,i1,i2);
    POST_USER_CALL(glEvalMesh1,glEvalMesh1(mode,i1,i2))
}

void GLAPIENTRY glEvalMesh2(GLenum mode, GLint i1, GLint i2, GLint j1, GLint j2)
{
    gli().init();
    PREV_USER_CALL(glEvalMesh2,glEvalMesh2(mode,i1,i2,j1,j2))
    glCalls().glEvalMesh2(mode,i1,i2,j1,j2);
    POST_USER_CALL(glEvalMesh2,glEvalMesh2(mode,i1,i2,j1,j2))
}

void GLAPIENTRY glEvalPoint1(GLint i)
{
    gli().init();
    PREV_USER_CALL(glEvalPoint1,glEvalPoint1(i))
    glCalls().glEvalPoint1(i);
    POST_USER_CALL(glEvalPoint1,glEvalPoint1(i))
}

void GLAPIENTRY glEvalPoint2(GLint i, GLint j)
{
    gli().init();
    PREV_USER_CALL(glEvalPoint2,glEvalPoint2(i,j))
    glCalls().glEvalPoint2(i,j);
    POST_USER_CALL(glEvalPoint2,glEvalPoint2(i,j))
}

void GLAPIENTRY glExecuteProgramNV(GLenum _p0, GLuint _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glExecuteProgramNV,glExecuteProgramNV(_p0,_p1,_p2))
    glCalls().glExecuteProgramNV(_p0,_p1,_p2);
    POST_USER_CALL(glExecuteProgramNV,glExecuteProgramNV(_p0,_p1,_p2))
}

void GLAPIENTRY glExtractComponentEXT(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glExtractComponentEXT,glExtractComponentEXT(_p0,_p1,_p2))
    glCalls().glExtractComponentEXT(_p0,_p1,_p2);
    POST_USER_CALL(glExtractComponentEXT,glExtractComponentEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glFeedbackBuffer(GLsizei size, GLenum type, GLfloat *buffer)
{
    gli().init();
    PREV_USER_CALL(glFeedbackBuffer,glFeedbackBuffer(size,type,buffer))
    glCalls().glFeedbackBuffer(size,type,buffer);
    POST_USER_CALL(glFeedbackBuffer,glFeedbackBuffer(size,type,buffer))
}

void GLAPIENTRY glFinalCombinerInputNV(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glFinalCombinerInputNV,glFinalCombinerInputNV(_p0,_p1,_p2,_p3))
    glCalls().glFinalCombinerInputNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glFinalCombinerInputNV,glFinalCombinerInputNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glFinish()
{
    gli().init();
    PREV_USER_CALL(glFinish,glFinish())
    glCalls().glFinish();
    POST_USER_CALL(glFinish,glFinish())
}

GLint GLAPIENTRY glFinishAsyncSGIX(GLuint *_p0)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glFinishAsyncSGIX,glFinishAsyncSGIX(_p0))
    _result = glCalls().glFinishAsyncSGIX(_p0);
    POST_USER_CALL(glFinishAsyncSGIX,glFinishAsyncSGIX(_p0))
    return _result;
}

void GLAPIENTRY glFinishFenceAPPLE(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glFinishFenceAPPLE,glFinishFenceAPPLE(_p0))
    glCalls().glFinishFenceAPPLE(_p0);
    POST_USER_CALL(glFinishFenceAPPLE,glFinishFenceAPPLE(_p0))
}

void GLAPIENTRY glFinishFenceNV(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glFinishFenceNV,glFinishFenceNV(_p0))
    glCalls().glFinishFenceNV(_p0);
    POST_USER_CALL(glFinishFenceNV,glFinishFenceNV(_p0))
}

void GLAPIENTRY glFinishObjectAPPLE(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glFinishObjectAPPLE,glFinishObjectAPPLE(_p0,_p1))
    glCalls().glFinishObjectAPPLE(_p0,_p1);
    POST_USER_CALL(glFinishObjectAPPLE,glFinishObjectAPPLE(_p0,_p1))
}

void GLAPIENTRY glFlush()
{
    gli().init();
    PREV_USER_CALL(glFlush,glFlush())
    glCalls().glFlush();
    POST_USER_CALL(glFlush,glFlush())
}

void GLAPIENTRY glFlushMappedBufferRange(GLenum _p0, GLintptr _p1, GLsizeiptr _p2)
{
    gli().init();
    PREV_USER_CALL(glFlushMappedBufferRange,glFlushMappedBufferRange(_p0,_p1,_p2))
    glCalls().glFlushMappedBufferRange(_p0,_p1,_p2);
    POST_USER_CALL(glFlushMappedBufferRange,glFlushMappedBufferRange(_p0,_p1,_p2))
}

void GLAPIENTRY glFlushMappedBufferRangeAPPLE(GLenum _p0, GLintptr _p1, GLsizeiptr _p2)
{
    gli().init();
    PREV_USER_CALL(glFlushMappedBufferRangeAPPLE,glFlushMappedBufferRangeAPPLE(_p0,_p1,_p2))
    glCalls().glFlushMappedBufferRangeAPPLE(_p0,_p1,_p2);
    POST_USER_CALL(glFlushMappedBufferRangeAPPLE,glFlushMappedBufferRangeAPPLE(_p0,_p1,_p2))
}

void GLAPIENTRY glFlushPixelDataRangeNV(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glFlushPixelDataRangeNV,glFlushPixelDataRangeNV(_p0))
    glCalls().glFlushPixelDataRangeNV(_p0);
    POST_USER_CALL(glFlushPixelDataRangeNV,glFlushPixelDataRangeNV(_p0))
}

void GLAPIENTRY glFlushRasterSGIX()
{
    gli().init();
    PREV_USER_CALL(glFlushRasterSGIX,glFlushRasterSGIX())
    glCalls().glFlushRasterSGIX();
    POST_USER_CALL(glFlushRasterSGIX,glFlushRasterSGIX())
}

void GLAPIENTRY glFlushVertexArrayRangeAPPLE(GLsizei _p0, GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glFlushVertexArrayRangeAPPLE,glFlushVertexArrayRangeAPPLE(_p0,_p1))
    glCalls().glFlushVertexArrayRangeAPPLE(_p0,_p1);
    POST_USER_CALL(glFlushVertexArrayRangeAPPLE,glFlushVertexArrayRangeAPPLE(_p0,_p1))
}

void GLAPIENTRY glFlushVertexArrayRangeNV()
{
    gli().init();
    PREV_USER_CALL(glFlushVertexArrayRangeNV,glFlushVertexArrayRangeNV())
    glCalls().glFlushVertexArrayRangeNV();
    POST_USER_CALL(glFlushVertexArrayRangeNV,glFlushVertexArrayRangeNV())
}

void GLAPIENTRY glFogCoordPointer(GLenum _p0, GLsizei _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glFogCoordPointer,glFogCoordPointer(_p0,_p1,_p2))
    glCalls().glFogCoordPointer(_p0,_p1,_p2);
    POST_USER_CALL(glFogCoordPointer,glFogCoordPointer(_p0,_p1,_p2))
}

void GLAPIENTRY glFogCoordPointerEXT(GLenum _p0, GLsizei _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glFogCoordPointerEXT,glFogCoordPointerEXT(_p0,_p1,_p2))
    glCalls().glFogCoordPointerEXT(_p0,_p1,_p2);
    POST_USER_CALL(glFogCoordPointerEXT,glFogCoordPointerEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glFogCoordd(GLdouble _p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordd,glFogCoordd(_p0))
    glCalls().glFogCoordd(_p0);
    POST_USER_CALL(glFogCoordd,glFogCoordd(_p0))
}

void GLAPIENTRY glFogCoorddEXT(GLdouble _p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoorddEXT,glFogCoorddEXT(_p0))
    glCalls().glFogCoorddEXT(_p0);
    POST_USER_CALL(glFogCoorddEXT,glFogCoorddEXT(_p0))
}

void GLAPIENTRY glFogCoorddv(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoorddv,glFogCoorddv(_p0))
    glCalls().glFogCoorddv(_p0);
    POST_USER_CALL(glFogCoorddv,glFogCoorddv(_p0))
}

void GLAPIENTRY glFogCoorddvEXT(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoorddvEXT,glFogCoorddvEXT(_p0))
    glCalls().glFogCoorddvEXT(_p0);
    POST_USER_CALL(glFogCoorddvEXT,glFogCoorddvEXT(_p0))
}

void GLAPIENTRY glFogCoordf(GLfloat _p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordf,glFogCoordf(_p0))
    glCalls().glFogCoordf(_p0);
    POST_USER_CALL(glFogCoordf,glFogCoordf(_p0))
}

void GLAPIENTRY glFogCoordfEXT(GLfloat _p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordfEXT,glFogCoordfEXT(_p0))
    glCalls().glFogCoordfEXT(_p0);
    POST_USER_CALL(glFogCoordfEXT,glFogCoordfEXT(_p0))
}

void GLAPIENTRY glFogCoordfv(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordfv,glFogCoordfv(_p0))
    glCalls().glFogCoordfv(_p0);
    POST_USER_CALL(glFogCoordfv,glFogCoordfv(_p0))
}

void GLAPIENTRY glFogCoordfvEXT(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordfvEXT,glFogCoordfvEXT(_p0))
    glCalls().glFogCoordfvEXT(_p0);
    POST_USER_CALL(glFogCoordfvEXT,glFogCoordfvEXT(_p0))
}

void GLAPIENTRY glFogCoordhNV(GLhalfNV _p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordhNV,glFogCoordhNV(_p0))
    glCalls().glFogCoordhNV(_p0);
    POST_USER_CALL(glFogCoordhNV,glFogCoordhNV(_p0))
}

void GLAPIENTRY glFogCoordhvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glFogCoordhvNV,glFogCoordhvNV(_p0))
    glCalls().glFogCoordhvNV(_p0);
    POST_USER_CALL(glFogCoordhvNV,glFogCoordhvNV(_p0))
}

void GLAPIENTRY glFogFuncSGIS(GLsizei _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glFogFuncSGIS,glFogFuncSGIS(_p0,_p1))
    glCalls().glFogFuncSGIS(_p0,_p1);
    POST_USER_CALL(glFogFuncSGIS,glFogFuncSGIS(_p0,_p1))
}

void GLAPIENTRY glFogf(GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glFogf,glFogf(pname,param))
    glCalls().glFogf(pname,param);
    POST_USER_CALL(glFogf,glFogf(pname,param))
}

void GLAPIENTRY glFogfv(GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glFogfv,glFogfv(pname,params))
    glCalls().glFogfv(pname,params);
    POST_USER_CALL(glFogfv,glFogfv(pname,params))
}

void GLAPIENTRY glFogi(GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glFogi,glFogi(pname,param))
    glCalls().glFogi(pname,param);
    POST_USER_CALL(glFogi,glFogi(pname,param))
}

void GLAPIENTRY glFogiv(GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glFogiv,glFogiv(pname,params))
    glCalls().glFogiv(pname,params);
    POST_USER_CALL(glFogiv,glFogiv(pname,params))
}

void GLAPIENTRY glFragmentColorMaterialSGIX(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glFragmentColorMaterialSGIX,glFragmentColorMaterialSGIX(_p0,_p1))
    glCalls().glFragmentColorMaterialSGIX(_p0,_p1);
    POST_USER_CALL(glFragmentColorMaterialSGIX,glFragmentColorMaterialSGIX(_p0,_p1))
}

void GLAPIENTRY glFragmentLightModelfSGIX(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightModelfSGIX,glFragmentLightModelfSGIX(_p0,_p1))
    glCalls().glFragmentLightModelfSGIX(_p0,_p1);
    POST_USER_CALL(glFragmentLightModelfSGIX,glFragmentLightModelfSGIX(_p0,_p1))
}

void GLAPIENTRY glFragmentLightModelfvSGIX(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightModelfvSGIX,glFragmentLightModelfvSGIX(_p0,_p1))
    glCalls().glFragmentLightModelfvSGIX(_p0,_p1);
    POST_USER_CALL(glFragmentLightModelfvSGIX,glFragmentLightModelfvSGIX(_p0,_p1))
}

void GLAPIENTRY glFragmentLightModeliSGIX(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightModeliSGIX,glFragmentLightModeliSGIX(_p0,_p1))
    glCalls().glFragmentLightModeliSGIX(_p0,_p1);
    POST_USER_CALL(glFragmentLightModeliSGIX,glFragmentLightModeliSGIX(_p0,_p1))
}

void GLAPIENTRY glFragmentLightModelivSGIX(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightModelivSGIX,glFragmentLightModelivSGIX(_p0,_p1))
    glCalls().glFragmentLightModelivSGIX(_p0,_p1);
    POST_USER_CALL(glFragmentLightModelivSGIX,glFragmentLightModelivSGIX(_p0,_p1))
}

void GLAPIENTRY glFragmentLightfSGIX(GLenum _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightfSGIX,glFragmentLightfSGIX(_p0,_p1,_p2))
    glCalls().glFragmentLightfSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentLightfSGIX,glFragmentLightfSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentLightfvSGIX(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightfvSGIX,glFragmentLightfvSGIX(_p0,_p1,_p2))
    glCalls().glFragmentLightfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentLightfvSGIX,glFragmentLightfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentLightiSGIX(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightiSGIX,glFragmentLightiSGIX(_p0,_p1,_p2))
    glCalls().glFragmentLightiSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentLightiSGIX,glFragmentLightiSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentLightivSGIX(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentLightivSGIX,glFragmentLightivSGIX(_p0,_p1,_p2))
    glCalls().glFragmentLightivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentLightivSGIX,glFragmentLightivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentMaterialfSGIX(GLenum _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentMaterialfSGIX,glFragmentMaterialfSGIX(_p0,_p1,_p2))
    glCalls().glFragmentMaterialfSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentMaterialfSGIX,glFragmentMaterialfSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentMaterialfvSGIX(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentMaterialfvSGIX,glFragmentMaterialfvSGIX(_p0,_p1,_p2))
    glCalls().glFragmentMaterialfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentMaterialfvSGIX,glFragmentMaterialfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentMaterialiSGIX(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentMaterialiSGIX,glFragmentMaterialiSGIX(_p0,_p1,_p2))
    glCalls().glFragmentMaterialiSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentMaterialiSGIX,glFragmentMaterialiSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFragmentMaterialivSGIX(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glFragmentMaterialivSGIX,glFragmentMaterialivSGIX(_p0,_p1,_p2))
    glCalls().glFragmentMaterialivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glFragmentMaterialivSGIX,glFragmentMaterialivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glFrameTerminatorGREMEDY()
{
    gli().init();
    PREV_USER_CALL(glFrameTerminatorGREMEDY,glFrameTerminatorGREMEDY())
    glCalls().glFrameTerminatorGREMEDY();
    POST_USER_CALL(glFrameTerminatorGREMEDY,glFrameTerminatorGREMEDY())
}

void GLAPIENTRY glFrameZoomSGIX(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glFrameZoomSGIX,glFrameZoomSGIX(_p0))
    glCalls().glFrameZoomSGIX(_p0);
    POST_USER_CALL(glFrameZoomSGIX,glFrameZoomSGIX(_p0))
}

void GLAPIENTRY glFramebufferDrawBufferEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glFramebufferDrawBufferEXT,glFramebufferDrawBufferEXT(_p0,_p1))
    glCalls().glFramebufferDrawBufferEXT(_p0,_p1);
    POST_USER_CALL(glFramebufferDrawBufferEXT,glFramebufferDrawBufferEXT(_p0,_p1))
}

void GLAPIENTRY glFramebufferDrawBuffersEXT(GLuint _p0, GLsizei _p1, const GLenum *_p2)
{
    gli().init();
    PREV_USER_CALL(glFramebufferDrawBuffersEXT,glFramebufferDrawBuffersEXT(_p0,_p1,_p2))
    glCalls().glFramebufferDrawBuffersEXT(_p0,_p1,_p2);
    POST_USER_CALL(glFramebufferDrawBuffersEXT,glFramebufferDrawBuffersEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glFramebufferReadBufferEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glFramebufferReadBufferEXT,glFramebufferReadBufferEXT(_p0,_p1))
    glCalls().glFramebufferReadBufferEXT(_p0,_p1);
    POST_USER_CALL(glFramebufferReadBufferEXT,glFramebufferReadBufferEXT(_p0,_p1))
}

void GLAPIENTRY glFramebufferRenderbuffer(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glFramebufferRenderbuffer,glFramebufferRenderbuffer(_p0,_p1,_p2,_p3))
    glCalls().glFramebufferRenderbuffer(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glFramebufferRenderbuffer,glFramebufferRenderbuffer(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glFramebufferRenderbufferEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glFramebufferRenderbufferEXT,glFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3))
    glCalls().glFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glFramebufferRenderbufferEXT,glFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glFramebufferTexture1D(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture1D,glFramebufferTexture1D(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTexture1D(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTexture1D,glFramebufferTexture1D(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTexture1DEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture1DEXT,glFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTexture1DEXT,glFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTexture2D(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture2D,glFramebufferTexture2D(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTexture2D(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTexture2D,glFramebufferTexture2D(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTexture2DEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture2DEXT,glFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTexture2DEXT,glFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTexture3D(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture3D,glFramebufferTexture3D(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glFramebufferTexture3D(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glFramebufferTexture3D,glFramebufferTexture3D(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glFramebufferTexture3DEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTexture3DEXT,glFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glFramebufferTexture3DEXT,glFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glFramebufferTextureARB(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureARB,glFramebufferTextureARB(_p0,_p1,_p2,_p3))
    glCalls().glFramebufferTextureARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glFramebufferTextureARB,glFramebufferTextureARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glFramebufferTextureEXT(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureEXT,glFramebufferTextureEXT(_p0,_p1,_p2,_p3))
    glCalls().glFramebufferTextureEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glFramebufferTextureEXT,glFramebufferTextureEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glFramebufferTextureFaceARB(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3, GLenum _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureFaceARB,glFramebufferTextureFaceARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTextureFaceARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTextureFaceARB,glFramebufferTextureFaceARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTextureFaceEXT(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3, GLenum _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureFaceEXT,glFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTextureFaceEXT,glFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTextureLayer(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureLayer,glFramebufferTextureLayer(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTextureLayer(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTextureLayer,glFramebufferTextureLayer(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTextureLayerARB(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureLayerARB,glFramebufferTextureLayerARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTextureLayerARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTextureLayerARB,glFramebufferTextureLayerARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFramebufferTextureLayerEXT(GLenum _p0, GLenum _p1, GLuint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glFramebufferTextureLayerEXT,glFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glFramebufferTextureLayerEXT,glFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glFreeObjectBufferATI(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glFreeObjectBufferATI,glFreeObjectBufferATI(_p0))
    glCalls().glFreeObjectBufferATI(_p0);
    POST_USER_CALL(glFreeObjectBufferATI,glFreeObjectBufferATI(_p0))
}

void GLAPIENTRY glFrontFace(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glFrontFace,glFrontFace(mode))
    glCalls().glFrontFace(mode);
    POST_USER_CALL(glFrontFace,glFrontFace(mode))
}

void GLAPIENTRY glFrustum(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)
{
    gli().init();
    PREV_USER_CALL(glFrustum,glFrustum(left,right,bottom,top,near_val,far_val))
    glCalls().glFrustum(left,right,bottom,top,near_val,far_val);
    POST_USER_CALL(glFrustum,glFrustum(left,right,bottom,top,near_val,far_val))
}

GLuint GLAPIENTRY glGenAsyncMarkersSGIX(GLsizei _p0)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGenAsyncMarkersSGIX,glGenAsyncMarkersSGIX(_p0))
    _result = glCalls().glGenAsyncMarkersSGIX(_p0);
    POST_USER_CALL(glGenAsyncMarkersSGIX,glGenAsyncMarkersSGIX(_p0))
    return _result;
}

void GLAPIENTRY glGenBuffers(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenBuffers,glGenBuffers(_p0,_p1))
    glCalls().glGenBuffers(_p0,_p1);
    POST_USER_CALL(glGenBuffers,glGenBuffers(_p0,_p1))
}

void GLAPIENTRY glGenBuffersARB(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenBuffersARB,glGenBuffersARB(_p0,_p1))
    glCalls().glGenBuffersARB(_p0,_p1);
    POST_USER_CALL(glGenBuffersARB,glGenBuffersARB(_p0,_p1))
}

void GLAPIENTRY glGenFencesAPPLE(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenFencesAPPLE,glGenFencesAPPLE(_p0,_p1))
    glCalls().glGenFencesAPPLE(_p0,_p1);
    POST_USER_CALL(glGenFencesAPPLE,glGenFencesAPPLE(_p0,_p1))
}

void GLAPIENTRY glGenFencesNV(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenFencesNV,glGenFencesNV(_p0,_p1))
    glCalls().glGenFencesNV(_p0,_p1);
    POST_USER_CALL(glGenFencesNV,glGenFencesNV(_p0,_p1))
}

GLuint GLAPIENTRY glGenFragmentShadersATI(GLuint _p0)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGenFragmentShadersATI,glGenFragmentShadersATI(_p0))
    _result = glCalls().glGenFragmentShadersATI(_p0);
    POST_USER_CALL(glGenFragmentShadersATI,glGenFragmentShadersATI(_p0))
    return _result;
}

void GLAPIENTRY glGenFramebuffers(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenFramebuffers,glGenFramebuffers(_p0,_p1))
    glCalls().glGenFramebuffers(_p0,_p1);
    POST_USER_CALL(glGenFramebuffers,glGenFramebuffers(_p0,_p1))
}

void GLAPIENTRY glGenFramebuffersEXT(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenFramebuffersEXT,glGenFramebuffersEXT(_p0,_p1))
    glCalls().glGenFramebuffersEXT(_p0,_p1);
    POST_USER_CALL(glGenFramebuffersEXT,glGenFramebuffersEXT(_p0,_p1))
}

GLuint GLAPIENTRY glGenLists(GLsizei range)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGenLists,glGenLists(range))
    _result = glCalls().glGenLists(range);
    POST_USER_CALL(glGenLists,glGenLists(range))
    return _result;
}

void GLAPIENTRY glGenOcclusionQueriesNV(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenOcclusionQueriesNV,glGenOcclusionQueriesNV(_p0,_p1))
    glCalls().glGenOcclusionQueriesNV(_p0,_p1);
    POST_USER_CALL(glGenOcclusionQueriesNV,glGenOcclusionQueriesNV(_p0,_p1))
}

void GLAPIENTRY glGenPerfMonitorsAMD(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenPerfMonitorsAMD,glGenPerfMonitorsAMD(_p0,_p1))
    glCalls().glGenPerfMonitorsAMD(_p0,_p1);
    POST_USER_CALL(glGenPerfMonitorsAMD,glGenPerfMonitorsAMD(_p0,_p1))
}

void GLAPIENTRY glGenProgramsARB(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenProgramsARB,glGenProgramsARB(_p0,_p1))
    glCalls().glGenProgramsARB(_p0,_p1);
    POST_USER_CALL(glGenProgramsARB,glGenProgramsARB(_p0,_p1))
}

void GLAPIENTRY glGenProgramsNV(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenProgramsNV,glGenProgramsNV(_p0,_p1))
    glCalls().glGenProgramsNV(_p0,_p1);
    POST_USER_CALL(glGenProgramsNV,glGenProgramsNV(_p0,_p1))
}

void GLAPIENTRY glGenQueries(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenQueries,glGenQueries(_p0,_p1))
    glCalls().glGenQueries(_p0,_p1);
    POST_USER_CALL(glGenQueries,glGenQueries(_p0,_p1))
}

void GLAPIENTRY glGenQueriesARB(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenQueriesARB,glGenQueriesARB(_p0,_p1))
    glCalls().glGenQueriesARB(_p0,_p1);
    POST_USER_CALL(glGenQueriesARB,glGenQueriesARB(_p0,_p1))
}

void GLAPIENTRY glGenRenderbuffers(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenRenderbuffers,glGenRenderbuffers(_p0,_p1))
    glCalls().glGenRenderbuffers(_p0,_p1);
    POST_USER_CALL(glGenRenderbuffers,glGenRenderbuffers(_p0,_p1))
}

void GLAPIENTRY glGenRenderbuffersEXT(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenRenderbuffersEXT,glGenRenderbuffersEXT(_p0,_p1))
    glCalls().glGenRenderbuffersEXT(_p0,_p1);
    POST_USER_CALL(glGenRenderbuffersEXT,glGenRenderbuffersEXT(_p0,_p1))
}

GLuint GLAPIENTRY glGenSymbolsEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGenSymbolsEXT,glGenSymbolsEXT(_p0,_p1,_p2,_p3))
    _result = glCalls().glGenSymbolsEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGenSymbolsEXT,glGenSymbolsEXT(_p0,_p1,_p2,_p3))
    return _result;
}

void GLAPIENTRY glGenTextures(GLsizei n, GLuint *textures)
{
    gli().init();
    PREV_USER_CALL(glGenTextures,glGenTextures(n,textures))
    glCalls().glGenTextures(n,textures);
    POST_USER_CALL(glGenTextures,glGenTextures(n,textures))
}

void GLAPIENTRY glGenTexturesEXT(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenTexturesEXT,glGenTexturesEXT(_p0,_p1))
    glCalls().glGenTexturesEXT(_p0,_p1);
    POST_USER_CALL(glGenTexturesEXT,glGenTexturesEXT(_p0,_p1))
}

void GLAPIENTRY glGenTransformFeedbacksNV(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenTransformFeedbacksNV,glGenTransformFeedbacksNV(_p0,_p1))
    glCalls().glGenTransformFeedbacksNV(_p0,_p1);
    POST_USER_CALL(glGenTransformFeedbacksNV,glGenTransformFeedbacksNV(_p0,_p1))
}

void GLAPIENTRY glGenVertexArrays(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenVertexArrays,glGenVertexArrays(_p0,_p1))
    glCalls().glGenVertexArrays(_p0,_p1);
    POST_USER_CALL(glGenVertexArrays,glGenVertexArrays(_p0,_p1))
}

void GLAPIENTRY glGenVertexArraysAPPLE(GLsizei _p0, GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGenVertexArraysAPPLE,glGenVertexArraysAPPLE(_p0,_p1))
    glCalls().glGenVertexArraysAPPLE(_p0,_p1);
    POST_USER_CALL(glGenVertexArraysAPPLE,glGenVertexArraysAPPLE(_p0,_p1))
}

GLuint GLAPIENTRY glGenVertexShadersEXT(GLuint _p0)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGenVertexShadersEXT,glGenVertexShadersEXT(_p0))
    _result = glCalls().glGenVertexShadersEXT(_p0);
    POST_USER_CALL(glGenVertexShadersEXT,glGenVertexShadersEXT(_p0))
    return _result;
}

void GLAPIENTRY glGenerateMipmap(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glGenerateMipmap,glGenerateMipmap(_p0))
    glCalls().glGenerateMipmap(_p0);
    POST_USER_CALL(glGenerateMipmap,glGenerateMipmap(_p0))
}

void GLAPIENTRY glGenerateMipmapEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glGenerateMipmapEXT,glGenerateMipmapEXT(_p0))
    glCalls().glGenerateMipmapEXT(_p0);
    POST_USER_CALL(glGenerateMipmapEXT,glGenerateMipmapEXT(_p0))
}

void GLAPIENTRY glGenerateMultiTexMipmapEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glGenerateMultiTexMipmapEXT,glGenerateMultiTexMipmapEXT(_p0,_p1))
    glCalls().glGenerateMultiTexMipmapEXT(_p0,_p1);
    POST_USER_CALL(glGenerateMultiTexMipmapEXT,glGenerateMultiTexMipmapEXT(_p0,_p1))
}

void GLAPIENTRY glGenerateTextureMipmapEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glGenerateTextureMipmapEXT,glGenerateTextureMipmapEXT(_p0,_p1))
    glCalls().glGenerateTextureMipmapEXT(_p0,_p1);
    POST_USER_CALL(glGenerateTextureMipmapEXT,glGenerateTextureMipmapEXT(_p0,_p1))
}

void GLAPIENTRY glGetActiveAttrib(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLint *_p4, GLenum *_p5, GLchar *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetActiveAttrib,glGetActiveAttrib(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetActiveAttrib(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetActiveAttrib,glGetActiveAttrib(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetActiveAttribARB(GLhandleARB _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLint *_p4, GLenum *_p5, GLcharARB *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetActiveAttribARB,glGetActiveAttribARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetActiveAttribARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetActiveAttribARB,glGetActiveAttribARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetActiveUniform(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLint *_p4, GLenum *_p5, GLchar *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniform,glGetActiveUniform(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetActiveUniform(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetActiveUniform,glGetActiveUniform(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetActiveUniformARB(GLhandleARB _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLint *_p4, GLenum *_p5, GLcharARB *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniformARB,glGetActiveUniformARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetActiveUniformARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetActiveUniformARB,glGetActiveUniformARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetActiveUniformBlockName(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLchar *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniformBlockName,glGetActiveUniformBlockName(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetActiveUniformBlockName(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetActiveUniformBlockName,glGetActiveUniformBlockName(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetActiveUniformBlockiv(GLuint _p0, GLuint _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniformBlockiv,glGetActiveUniformBlockiv(_p0,_p1,_p2,_p3))
    glCalls().glGetActiveUniformBlockiv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetActiveUniformBlockiv,glGetActiveUniformBlockiv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetActiveUniformName(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLchar *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniformName,glGetActiveUniformName(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetActiveUniformName(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetActiveUniformName,glGetActiveUniformName(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetActiveUniformsiv(GLuint _p0, GLsizei _p1, const GLuint *_p2, GLenum _p3, GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetActiveUniformsiv,glGetActiveUniformsiv(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetActiveUniformsiv(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetActiveUniformsiv,glGetActiveUniformsiv(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetActiveVaryingNV(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLsizei *_p4, GLenum *_p5, GLchar *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetActiveVaryingNV,glGetActiveVaryingNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetActiveVaryingNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetActiveVaryingNV,glGetActiveVaryingNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetArrayObjectfvATI(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetArrayObjectfvATI,glGetArrayObjectfvATI(_p0,_p1,_p2))
    glCalls().glGetArrayObjectfvATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetArrayObjectfvATI,glGetArrayObjectfvATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetArrayObjectivATI(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetArrayObjectivATI,glGetArrayObjectivATI(_p0,_p1,_p2))
    glCalls().glGetArrayObjectivATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetArrayObjectivATI,glGetArrayObjectivATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetAttachedObjectsARB(GLhandleARB _p0, GLsizei _p1, GLsizei *_p2, GLhandleARB *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetAttachedObjectsARB,glGetAttachedObjectsARB(_p0,_p1,_p2,_p3))
    glCalls().glGetAttachedObjectsARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetAttachedObjectsARB,glGetAttachedObjectsARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetAttachedShaders(GLuint _p0, GLsizei _p1, GLsizei *_p2, GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetAttachedShaders,glGetAttachedShaders(_p0,_p1,_p2,_p3))
    glCalls().glGetAttachedShaders(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetAttachedShaders,glGetAttachedShaders(_p0,_p1,_p2,_p3))
}

GLint GLAPIENTRY glGetAttribLocation(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetAttribLocation,glGetAttribLocation(_p0,_p1))
    _result = glCalls().glGetAttribLocation(_p0,_p1);
    POST_USER_CALL(glGetAttribLocation,glGetAttribLocation(_p0,_p1))
    return _result;
}

GLint GLAPIENTRY glGetAttribLocationARB(GLhandleARB _p0, const GLcharARB *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetAttribLocationARB,glGetAttribLocationARB(_p0,_p1))
    _result = glCalls().glGetAttribLocationARB(_p0,_p1);
    POST_USER_CALL(glGetAttribLocationARB,glGetAttribLocationARB(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetBooleanIndexedvEXT(GLenum _p0, GLuint _p1, GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBooleanIndexedvEXT,glGetBooleanIndexedvEXT(_p0,_p1,_p2))
    glCalls().glGetBooleanIndexedvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetBooleanIndexedvEXT,glGetBooleanIndexedvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBooleani_v(GLenum _p0, GLuint _p1, GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBooleani_v,glGetBooleani_v(_p0,_p1,_p2))
    glCalls().glGetBooleani_v(_p0,_p1,_p2);
    POST_USER_CALL(glGetBooleani_v,glGetBooleani_v(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBooleanv(GLenum pname, GLboolean *params)
{
    gli().init();
    PREV_USER_CALL(glGetBooleanv,glGetBooleanv(pname,params))
    glCalls().glGetBooleanv(pname,params);
    POST_USER_CALL(glGetBooleanv,glGetBooleanv(pname,params))
}

void GLAPIENTRY glGetBufferParameteriv(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBufferParameteriv,glGetBufferParameteriv(_p0,_p1,_p2))
    glCalls().glGetBufferParameteriv(_p0,_p1,_p2);
    POST_USER_CALL(glGetBufferParameteriv,glGetBufferParameteriv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBufferParameterivARB(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBufferParameterivARB,glGetBufferParameterivARB(_p0,_p1,_p2))
    glCalls().glGetBufferParameterivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetBufferParameterivARB,glGetBufferParameterivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBufferPointerv(GLenum _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBufferPointerv,glGetBufferPointerv(_p0,_p1,_p2))
    glCalls().glGetBufferPointerv(_p0,_p1,_p2);
    POST_USER_CALL(glGetBufferPointerv,glGetBufferPointerv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBufferPointervARB(GLenum _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetBufferPointervARB,glGetBufferPointervARB(_p0,_p1,_p2))
    glCalls().glGetBufferPointervARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetBufferPointervARB,glGetBufferPointervARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetBufferSubData(GLenum _p0, GLintptr _p1, GLsizeiptr _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetBufferSubData,glGetBufferSubData(_p0,_p1,_p2,_p3))
    glCalls().glGetBufferSubData(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetBufferSubData,glGetBufferSubData(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetBufferSubDataARB(GLenum _p0, GLintptrARB _p1, GLsizeiptrARB _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetBufferSubDataARB,glGetBufferSubDataARB(_p0,_p1,_p2,_p3))
    glCalls().glGetBufferSubDataARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetBufferSubDataARB,glGetBufferSubDataARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetClipPlane(GLenum plane, GLdouble *equation)
{
    gli().init();
    PREV_USER_CALL(glGetClipPlane,glGetClipPlane(plane,equation))
    glCalls().glGetClipPlane(plane,equation);
    POST_USER_CALL(glGetClipPlane,glGetClipPlane(plane,equation))
}

void GLAPIENTRY glGetColorTable(GLenum target, GLenum format, GLenum type, GLvoid *table)
{
    gli().init();
    PREV_USER_CALL(glGetColorTable,glGetColorTable(target,format,type,table))
    glCalls().glGetColorTable(target,format,type,table);
    POST_USER_CALL(glGetColorTable,glGetColorTable(target,format,type,table))
}

void GLAPIENTRY glGetColorTableEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableEXT,glGetColorTableEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetColorTableEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetColorTableEXT,glGetColorTableEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetColorTableParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameterfv,glGetColorTableParameterfv(target,pname,params))
    glCalls().glGetColorTableParameterfv(target,pname,params);
    POST_USER_CALL(glGetColorTableParameterfv,glGetColorTableParameterfv(target,pname,params))
}

void GLAPIENTRY glGetColorTableParameterfvEXT(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameterfvEXT,glGetColorTableParameterfvEXT(_p0,_p1,_p2))
    glCalls().glGetColorTableParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetColorTableParameterfvEXT,glGetColorTableParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetColorTableParameterfvSGI(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameterfvSGI,glGetColorTableParameterfvSGI(_p0,_p1,_p2))
    glCalls().glGetColorTableParameterfvSGI(_p0,_p1,_p2);
    POST_USER_CALL(glGetColorTableParameterfvSGI,glGetColorTableParameterfvSGI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetColorTableParameteriv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameteriv,glGetColorTableParameteriv(target,pname,params))
    glCalls().glGetColorTableParameteriv(target,pname,params);
    POST_USER_CALL(glGetColorTableParameteriv,glGetColorTableParameteriv(target,pname,params))
}

void GLAPIENTRY glGetColorTableParameterivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameterivEXT,glGetColorTableParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetColorTableParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetColorTableParameterivEXT,glGetColorTableParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetColorTableParameterivSGI(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableParameterivSGI,glGetColorTableParameterivSGI(_p0,_p1,_p2))
    glCalls().glGetColorTableParameterivSGI(_p0,_p1,_p2);
    POST_USER_CALL(glGetColorTableParameterivSGI,glGetColorTableParameterivSGI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetColorTableSGI(GLenum _p0, GLenum _p1, GLenum _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetColorTableSGI,glGetColorTableSGI(_p0,_p1,_p2,_p3))
    glCalls().glGetColorTableSGI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetColorTableSGI,glGetColorTableSGI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetCombinerInputParameterfvNV(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3, GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetCombinerInputParameterfvNV,glGetCombinerInputParameterfvNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetCombinerInputParameterfvNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetCombinerInputParameterfvNV,glGetCombinerInputParameterfvNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetCombinerInputParameterivNV(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3, GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetCombinerInputParameterivNV,glGetCombinerInputParameterivNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetCombinerInputParameterivNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetCombinerInputParameterivNV,glGetCombinerInputParameterivNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetCombinerOutputParameterfvNV(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetCombinerOutputParameterfvNV,glGetCombinerOutputParameterfvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetCombinerOutputParameterfvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetCombinerOutputParameterfvNV,glGetCombinerOutputParameterfvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetCombinerOutputParameterivNV(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetCombinerOutputParameterivNV,glGetCombinerOutputParameterivNV(_p0,_p1,_p2,_p3))
    glCalls().glGetCombinerOutputParameterivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetCombinerOutputParameterivNV,glGetCombinerOutputParameterivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetCombinerStageParameterfvNV(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetCombinerStageParameterfvNV,glGetCombinerStageParameterfvNV(_p0,_p1,_p2))
    glCalls().glGetCombinerStageParameterfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetCombinerStageParameterfvNV,glGetCombinerStageParameterfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetCompressedMultiTexImageEXT(GLenum _p0, GLenum _p1, GLint _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetCompressedMultiTexImageEXT,glGetCompressedMultiTexImageEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetCompressedMultiTexImageEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetCompressedMultiTexImageEXT,glGetCompressedMultiTexImageEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetCompressedTexImage(GLenum target, GLint lod, GLvoid *img)
{
    gli().init();
    PREV_USER_CALL(glGetCompressedTexImage,glGetCompressedTexImage(target,lod,img))
    glCalls().glGetCompressedTexImage(target,lod,img);
    POST_USER_CALL(glGetCompressedTexImage,glGetCompressedTexImage(target,lod,img))
}

void GLAPIENTRY glGetCompressedTexImageARB(GLenum _p0, GLint _p1, GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetCompressedTexImageARB,glGetCompressedTexImageARB(_p0,_p1,_p2))
    glCalls().glGetCompressedTexImageARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetCompressedTexImageARB,glGetCompressedTexImageARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetCompressedTextureImageEXT(GLuint _p0, GLenum _p1, GLint _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetCompressedTextureImageEXT,glGetCompressedTextureImageEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetCompressedTextureImageEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetCompressedTextureImageEXT,glGetCompressedTextureImageEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetConvolutionFilter(GLenum target, GLenum format, GLenum type, GLvoid *image)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionFilter,glGetConvolutionFilter(target,format,type,image))
    glCalls().glGetConvolutionFilter(target,format,type,image);
    POST_USER_CALL(glGetConvolutionFilter,glGetConvolutionFilter(target,format,type,image))
}

void GLAPIENTRY glGetConvolutionFilterEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionFilterEXT,glGetConvolutionFilterEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetConvolutionFilterEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetConvolutionFilterEXT,glGetConvolutionFilterEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetConvolutionParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionParameterfv,glGetConvolutionParameterfv(target,pname,params))
    glCalls().glGetConvolutionParameterfv(target,pname,params);
    POST_USER_CALL(glGetConvolutionParameterfv,glGetConvolutionParameterfv(target,pname,params))
}

void GLAPIENTRY glGetConvolutionParameterfvEXT(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionParameterfvEXT,glGetConvolutionParameterfvEXT(_p0,_p1,_p2))
    glCalls().glGetConvolutionParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetConvolutionParameterfvEXT,glGetConvolutionParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetConvolutionParameteriv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionParameteriv,glGetConvolutionParameteriv(target,pname,params))
    glCalls().glGetConvolutionParameteriv(target,pname,params);
    POST_USER_CALL(glGetConvolutionParameteriv,glGetConvolutionParameteriv(target,pname,params))
}

void GLAPIENTRY glGetConvolutionParameterivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetConvolutionParameterivEXT,glGetConvolutionParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetConvolutionParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetConvolutionParameterivEXT,glGetConvolutionParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetDetailTexFuncSGIS(GLenum _p0, GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetDetailTexFuncSGIS,glGetDetailTexFuncSGIS(_p0,_p1))
    glCalls().glGetDetailTexFuncSGIS(_p0,_p1);
    POST_USER_CALL(glGetDetailTexFuncSGIS,glGetDetailTexFuncSGIS(_p0,_p1))
}

void GLAPIENTRY glGetDoubleIndexedvEXT(GLenum _p0, GLuint _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetDoubleIndexedvEXT,glGetDoubleIndexedvEXT(_p0,_p1,_p2))
    glCalls().glGetDoubleIndexedvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetDoubleIndexedvEXT,glGetDoubleIndexedvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetDoublev(GLenum pname, GLdouble *params)
{
    gli().init();
    PREV_USER_CALL(glGetDoublev,glGetDoublev(pname,params))
    glCalls().glGetDoublev(pname,params);
    POST_USER_CALL(glGetDoublev,glGetDoublev(pname,params))
}

GLenum GLAPIENTRY glGetError()
{
    gli().init();
    GLenum _result;
    PREV_USER_CALL(glGetError,glGetError())
    _result = glCalls().glGetError();
    POST_USER_CALL(glGetError,glGetError())
    return _result;
}

void GLAPIENTRY glGetFenceivNV(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFenceivNV,glGetFenceivNV(_p0,_p1,_p2))
    glCalls().glGetFenceivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetFenceivNV,glGetFenceivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFinalCombinerInputParameterfvNV(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFinalCombinerInputParameterfvNV,glGetFinalCombinerInputParameterfvNV(_p0,_p1,_p2))
    glCalls().glGetFinalCombinerInputParameterfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetFinalCombinerInputParameterfvNV,glGetFinalCombinerInputParameterfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFinalCombinerInputParameterivNV(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFinalCombinerInputParameterivNV,glGetFinalCombinerInputParameterivNV(_p0,_p1,_p2))
    glCalls().glGetFinalCombinerInputParameterivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetFinalCombinerInputParameterivNV,glGetFinalCombinerInputParameterivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFloatIndexedvEXT(GLenum _p0, GLuint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFloatIndexedvEXT,glGetFloatIndexedvEXT(_p0,_p1,_p2))
    glCalls().glGetFloatIndexedvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetFloatIndexedvEXT,glGetFloatIndexedvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFloatv(GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetFloatv,glGetFloatv(pname,params))
    glCalls().glGetFloatv(pname,params);
    POST_USER_CALL(glGetFloatv,glGetFloatv(pname,params))
}

void GLAPIENTRY glGetFogFuncSGIS(GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glGetFogFuncSGIS,glGetFogFuncSGIS(_p0))
    glCalls().glGetFogFuncSGIS(_p0);
    POST_USER_CALL(glGetFogFuncSGIS,glGetFogFuncSGIS(_p0))
}

GLint GLAPIENTRY glGetFragDataLocation(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetFragDataLocation,glGetFragDataLocation(_p0,_p1))
    _result = glCalls().glGetFragDataLocation(_p0,_p1);
    POST_USER_CALL(glGetFragDataLocation,glGetFragDataLocation(_p0,_p1))
    return _result;
}

GLint GLAPIENTRY glGetFragDataLocationEXT(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetFragDataLocationEXT,glGetFragDataLocationEXT(_p0,_p1))
    _result = glCalls().glGetFragDataLocationEXT(_p0,_p1);
    POST_USER_CALL(glGetFragDataLocationEXT,glGetFragDataLocationEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetFragmentLightfvSGIX(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFragmentLightfvSGIX,glGetFragmentLightfvSGIX(_p0,_p1,_p2))
    glCalls().glGetFragmentLightfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetFragmentLightfvSGIX,glGetFragmentLightfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFragmentLightivSGIX(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFragmentLightivSGIX,glGetFragmentLightivSGIX(_p0,_p1,_p2))
    glCalls().glGetFragmentLightivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetFragmentLightivSGIX,glGetFragmentLightivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFragmentMaterialfvSGIX(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFragmentMaterialfvSGIX,glGetFragmentMaterialfvSGIX(_p0,_p1,_p2))
    glCalls().glGetFragmentMaterialfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetFragmentMaterialfvSGIX,glGetFragmentMaterialfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFragmentMaterialivSGIX(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFragmentMaterialivSGIX,glGetFragmentMaterialivSGIX(_p0,_p1,_p2))
    glCalls().glGetFragmentMaterialivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetFragmentMaterialivSGIX,glGetFragmentMaterialivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetFramebufferAttachmentParameteriv(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetFramebufferAttachmentParameteriv,glGetFramebufferAttachmentParameteriv(_p0,_p1,_p2,_p3))
    glCalls().glGetFramebufferAttachmentParameteriv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetFramebufferAttachmentParameteriv,glGetFramebufferAttachmentParameteriv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetFramebufferAttachmentParameterivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetFramebufferAttachmentParameterivEXT,glGetFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetFramebufferAttachmentParameterivEXT,glGetFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetFramebufferParameterivEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetFramebufferParameterivEXT,glGetFramebufferParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetFramebufferParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetFramebufferParameterivEXT,glGetFramebufferParameterivEXT(_p0,_p1,_p2))
}

GLhandleARB GLAPIENTRY glGetHandleARB(GLenum _p0)
{
    gli().init();
    GLhandleARB _result;
    PREV_USER_CALL(glGetHandleARB,glGetHandleARB(_p0))
    _result = glCalls().glGetHandleARB(_p0);
    POST_USER_CALL(glGetHandleARB,glGetHandleARB(_p0))
    return _result;
}

void GLAPIENTRY glGetHistogram(GLenum target, GLboolean reset, GLenum format, GLenum type, GLvoid *values)
{
    gli().init();
    PREV_USER_CALL(glGetHistogram,glGetHistogram(target,reset,format,type,values))
    glCalls().glGetHistogram(target,reset,format,type,values);
    POST_USER_CALL(glGetHistogram,glGetHistogram(target,reset,format,type,values))
}

void GLAPIENTRY glGetHistogramEXT(GLenum _p0, GLboolean _p1, GLenum _p2, GLenum _p3, GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetHistogramEXT,glGetHistogramEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetHistogramEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetHistogramEXT,glGetHistogramEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetHistogramParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetHistogramParameterfv,glGetHistogramParameterfv(target,pname,params))
    glCalls().glGetHistogramParameterfv(target,pname,params);
    POST_USER_CALL(glGetHistogramParameterfv,glGetHistogramParameterfv(target,pname,params))
}

void GLAPIENTRY glGetHistogramParameterfvEXT(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetHistogramParameterfvEXT,glGetHistogramParameterfvEXT(_p0,_p1,_p2))
    glCalls().glGetHistogramParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetHistogramParameterfvEXT,glGetHistogramParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetHistogramParameteriv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetHistogramParameteriv,glGetHistogramParameteriv(target,pname,params))
    glCalls().glGetHistogramParameteriv(target,pname,params);
    POST_USER_CALL(glGetHistogramParameteriv,glGetHistogramParameteriv(target,pname,params))
}

void GLAPIENTRY glGetHistogramParameterivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetHistogramParameterivEXT,glGetHistogramParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetHistogramParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetHistogramParameterivEXT,glGetHistogramParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetImageTransformParameterfvHP(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetImageTransformParameterfvHP,glGetImageTransformParameterfvHP(_p0,_p1,_p2))
    glCalls().glGetImageTransformParameterfvHP(_p0,_p1,_p2);
    POST_USER_CALL(glGetImageTransformParameterfvHP,glGetImageTransformParameterfvHP(_p0,_p1,_p2))
}

void GLAPIENTRY glGetImageTransformParameterivHP(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetImageTransformParameterivHP,glGetImageTransformParameterivHP(_p0,_p1,_p2))
    glCalls().glGetImageTransformParameterivHP(_p0,_p1,_p2);
    POST_USER_CALL(glGetImageTransformParameterivHP,glGetImageTransformParameterivHP(_p0,_p1,_p2))
}

void GLAPIENTRY glGetInfoLogARB(GLhandleARB _p0, GLsizei _p1, GLsizei *_p2, GLcharARB *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetInfoLogARB,glGetInfoLogARB(_p0,_p1,_p2,_p3))
    glCalls().glGetInfoLogARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetInfoLogARB,glGetInfoLogARB(_p0,_p1,_p2,_p3))
}

GLint GLAPIENTRY glGetInstrumentsSGIX()
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetInstrumentsSGIX,glGetInstrumentsSGIX())
    _result = glCalls().glGetInstrumentsSGIX();
    POST_USER_CALL(glGetInstrumentsSGIX,glGetInstrumentsSGIX())
    return _result;
}

void GLAPIENTRY glGetIntegerIndexedvEXT(GLenum _p0, GLuint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetIntegerIndexedvEXT,glGetIntegerIndexedvEXT(_p0,_p1,_p2))
    glCalls().glGetIntegerIndexedvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetIntegerIndexedvEXT,glGetIntegerIndexedvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetIntegeri_v(GLenum _p0, GLuint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetIntegeri_v,glGetIntegeri_v(_p0,_p1,_p2))
    glCalls().glGetIntegeri_v(_p0,_p1,_p2);
    POST_USER_CALL(glGetIntegeri_v,glGetIntegeri_v(_p0,_p1,_p2))
}

void GLAPIENTRY glGetIntegerv(GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetIntegerv,glGetIntegerv(pname,params))
    glCalls().glGetIntegerv(pname,params);
    POST_USER_CALL(glGetIntegerv,glGetIntegerv(pname,params))
}

void GLAPIENTRY glGetInvariantBooleanvEXT(GLuint _p0, GLenum _p1, GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetInvariantBooleanvEXT,glGetInvariantBooleanvEXT(_p0,_p1,_p2))
    glCalls().glGetInvariantBooleanvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetInvariantBooleanvEXT,glGetInvariantBooleanvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetInvariantFloatvEXT(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetInvariantFloatvEXT,glGetInvariantFloatvEXT(_p0,_p1,_p2))
    glCalls().glGetInvariantFloatvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetInvariantFloatvEXT,glGetInvariantFloatvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetInvariantIntegervEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetInvariantIntegervEXT,glGetInvariantIntegervEXT(_p0,_p1,_p2))
    glCalls().glGetInvariantIntegervEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetInvariantIntegervEXT,glGetInvariantIntegervEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetLightfv(GLenum light, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetLightfv,glGetLightfv(light,pname,params))
    glCalls().glGetLightfv(light,pname,params);
    POST_USER_CALL(glGetLightfv,glGetLightfv(light,pname,params))
}

void GLAPIENTRY glGetLightiv(GLenum light, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetLightiv,glGetLightiv(light,pname,params))
    glCalls().glGetLightiv(light,pname,params);
    POST_USER_CALL(glGetLightiv,glGetLightiv(light,pname,params))
}

void GLAPIENTRY glGetListParameterfvSGIX(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetListParameterfvSGIX,glGetListParameterfvSGIX(_p0,_p1,_p2))
    glCalls().glGetListParameterfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetListParameterfvSGIX,glGetListParameterfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetListParameterivSGIX(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetListParameterivSGIX,glGetListParameterivSGIX(_p0,_p1,_p2))
    glCalls().glGetListParameterivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glGetListParameterivSGIX,glGetListParameterivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glGetLocalConstantBooleanvEXT(GLuint _p0, GLenum _p1, GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetLocalConstantBooleanvEXT,glGetLocalConstantBooleanvEXT(_p0,_p1,_p2))
    glCalls().glGetLocalConstantBooleanvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetLocalConstantBooleanvEXT,glGetLocalConstantBooleanvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetLocalConstantFloatvEXT(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetLocalConstantFloatvEXT,glGetLocalConstantFloatvEXT(_p0,_p1,_p2))
    glCalls().glGetLocalConstantFloatvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetLocalConstantFloatvEXT,glGetLocalConstantFloatvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetLocalConstantIntegervEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetLocalConstantIntegervEXT,glGetLocalConstantIntegervEXT(_p0,_p1,_p2))
    glCalls().glGetLocalConstantIntegervEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetLocalConstantIntegervEXT,glGetLocalConstantIntegervEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetMapAttribParameterfvNV(GLenum _p0, GLuint _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMapAttribParameterfvNV,glGetMapAttribParameterfvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetMapAttribParameterfvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMapAttribParameterfvNV,glGetMapAttribParameterfvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMapAttribParameterivNV(GLenum _p0, GLuint _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMapAttribParameterivNV,glGetMapAttribParameterivNV(_p0,_p1,_p2,_p3))
    glCalls().glGetMapAttribParameterivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMapAttribParameterivNV,glGetMapAttribParameterivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMapControlPointsNV(GLenum _p0, GLuint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLboolean _p5, GLvoid *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetMapControlPointsNV,glGetMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetMapControlPointsNV,glGetMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetMapParameterfvNV(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetMapParameterfvNV,glGetMapParameterfvNV(_p0,_p1,_p2))
    glCalls().glGetMapParameterfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetMapParameterfvNV,glGetMapParameterfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetMapParameterivNV(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetMapParameterivNV,glGetMapParameterivNV(_p0,_p1,_p2))
    glCalls().glGetMapParameterivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetMapParameterivNV,glGetMapParameterivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetMapdv(GLenum target, GLenum query, GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glGetMapdv,glGetMapdv(target,query,v))
    glCalls().glGetMapdv(target,query,v);
    POST_USER_CALL(glGetMapdv,glGetMapdv(target,query,v))
}

void GLAPIENTRY glGetMapfv(GLenum target, GLenum query, GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glGetMapfv,glGetMapfv(target,query,v))
    glCalls().glGetMapfv(target,query,v);
    POST_USER_CALL(glGetMapfv,glGetMapfv(target,query,v))
}

void GLAPIENTRY glGetMapiv(GLenum target, GLenum query, GLint *v)
{
    gli().init();
    PREV_USER_CALL(glGetMapiv,glGetMapiv(target,query,v))
    glCalls().glGetMapiv(target,query,v);
    POST_USER_CALL(glGetMapiv,glGetMapiv(target,query,v))
}

void GLAPIENTRY glGetMaterialfv(GLenum face, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetMaterialfv,glGetMaterialfv(face,pname,params))
    glCalls().glGetMaterialfv(face,pname,params);
    POST_USER_CALL(glGetMaterialfv,glGetMaterialfv(face,pname,params))
}

void GLAPIENTRY glGetMaterialiv(GLenum face, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetMaterialiv,glGetMaterialiv(face,pname,params))
    glCalls().glGetMaterialiv(face,pname,params);
    POST_USER_CALL(glGetMaterialiv,glGetMaterialiv(face,pname,params))
}

void GLAPIENTRY glGetMinmax(GLenum target, GLboolean reset, GLenum format, GLenum types, GLvoid *values)
{
    gli().init();
    PREV_USER_CALL(glGetMinmax,glGetMinmax(target,reset,format,types,values))
    glCalls().glGetMinmax(target,reset,format,types,values);
    POST_USER_CALL(glGetMinmax,glGetMinmax(target,reset,format,types,values))
}

void GLAPIENTRY glGetMinmaxEXT(GLenum _p0, GLboolean _p1, GLenum _p2, GLenum _p3, GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetMinmaxEXT,glGetMinmaxEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetMinmaxEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetMinmaxEXT,glGetMinmaxEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetMinmaxParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetMinmaxParameterfv,glGetMinmaxParameterfv(target,pname,params))
    glCalls().glGetMinmaxParameterfv(target,pname,params);
    POST_USER_CALL(glGetMinmaxParameterfv,glGetMinmaxParameterfv(target,pname,params))
}

void GLAPIENTRY glGetMinmaxParameterfvEXT(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetMinmaxParameterfvEXT,glGetMinmaxParameterfvEXT(_p0,_p1,_p2))
    glCalls().glGetMinmaxParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetMinmaxParameterfvEXT,glGetMinmaxParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetMinmaxParameteriv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetMinmaxParameteriv,glGetMinmaxParameteriv(target,pname,params))
    glCalls().glGetMinmaxParameteriv(target,pname,params);
    POST_USER_CALL(glGetMinmaxParameteriv,glGetMinmaxParameteriv(target,pname,params))
}

void GLAPIENTRY glGetMinmaxParameterivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetMinmaxParameterivEXT,glGetMinmaxParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetMinmaxParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetMinmaxParameterivEXT,glGetMinmaxParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetMultiTexEnvfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexEnvfvEXT,glGetMultiTexEnvfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexEnvfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexEnvfvEXT,glGetMultiTexEnvfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexEnvivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexEnvivEXT,glGetMultiTexEnvivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexEnvivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexEnvivEXT,glGetMultiTexEnvivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexGendvEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexGendvEXT,glGetMultiTexGendvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexGendvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexGendvEXT,glGetMultiTexGendvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexGenfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexGenfvEXT,glGetMultiTexGenfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexGenfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexGenfvEXT,glGetMultiTexGenfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexGenivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexGenivEXT,glGetMultiTexGenivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexGenivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexGenivEXT,glGetMultiTexGenivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexImageEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLenum _p4, GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexImageEXT,glGetMultiTexImageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glGetMultiTexImageEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glGetMultiTexImageEXT,glGetMultiTexImageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glGetMultiTexLevelParameterfvEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexLevelParameterfvEXT,glGetMultiTexLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetMultiTexLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetMultiTexLevelParameterfvEXT,glGetMultiTexLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetMultiTexLevelParameterivEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexLevelParameterivEXT,glGetMultiTexLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetMultiTexLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetMultiTexLevelParameterivEXT,glGetMultiTexLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetMultiTexParameterIivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexParameterIivEXT,glGetMultiTexParameterIivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexParameterIivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexParameterIivEXT,glGetMultiTexParameterIivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexParameterIuivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexParameterIuivEXT,glGetMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexParameterIuivEXT,glGetMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexParameterfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexParameterfvEXT,glGetMultiTexParameterfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexParameterfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexParameterfvEXT,glGetMultiTexParameterfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultiTexParameterivEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetMultiTexParameterivEXT,glGetMultiTexParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetMultiTexParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetMultiTexParameterivEXT,glGetMultiTexParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetMultisamplefvNV(GLenum _p0, GLuint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetMultisamplefvNV,glGetMultisamplefvNV(_p0,_p1,_p2))
    glCalls().glGetMultisamplefvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetMultisamplefvNV,glGetMultisamplefvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetNamedBufferParameterivEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetNamedBufferParameterivEXT,glGetNamedBufferParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetNamedBufferParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetNamedBufferParameterivEXT,glGetNamedBufferParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetNamedBufferPointervEXT(GLuint _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetNamedBufferPointervEXT,glGetNamedBufferPointervEXT(_p0,_p1,_p2))
    glCalls().glGetNamedBufferPointervEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetNamedBufferPointervEXT,glGetNamedBufferPointervEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetNamedBufferSubDataEXT(GLuint _p0, GLintptr _p1, GLsizeiptr _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedBufferSubDataEXT,glGetNamedBufferSubDataEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedBufferSubDataEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedBufferSubDataEXT,glGetNamedBufferSubDataEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedFramebufferAttachmentParameterivEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedFramebufferAttachmentParameterivEXT,glGetNamedFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedFramebufferAttachmentParameterivEXT,glGetNamedFramebufferAttachmentParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramLocalParameterIivEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramLocalParameterIivEXT,glGetNamedProgramLocalParameterIivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramLocalParameterIivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramLocalParameterIivEXT,glGetNamedProgramLocalParameterIivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramLocalParameterIuivEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramLocalParameterIuivEXT,glGetNamedProgramLocalParameterIuivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramLocalParameterIuivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramLocalParameterIuivEXT,glGetNamedProgramLocalParameterIuivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramLocalParameterdvEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramLocalParameterdvEXT,glGetNamedProgramLocalParameterdvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramLocalParameterdvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramLocalParameterdvEXT,glGetNamedProgramLocalParameterdvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramLocalParameterfvEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramLocalParameterfvEXT,glGetNamedProgramLocalParameterfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramLocalParameterfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramLocalParameterfvEXT,glGetNamedProgramLocalParameterfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramStringEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramStringEXT,glGetNamedProgramStringEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramStringEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramStringEXT,glGetNamedProgramStringEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedProgramivEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetNamedProgramivEXT,glGetNamedProgramivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetNamedProgramivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetNamedProgramivEXT,glGetNamedProgramivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetNamedRenderbufferParameterivEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetNamedRenderbufferParameterivEXT,glGetNamedRenderbufferParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetNamedRenderbufferParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetNamedRenderbufferParameterivEXT,glGetNamedRenderbufferParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetObjectBufferfvATI(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetObjectBufferfvATI,glGetObjectBufferfvATI(_p0,_p1,_p2))
    glCalls().glGetObjectBufferfvATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetObjectBufferfvATI,glGetObjectBufferfvATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetObjectBufferivATI(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetObjectBufferivATI,glGetObjectBufferivATI(_p0,_p1,_p2))
    glCalls().glGetObjectBufferivATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetObjectBufferivATI,glGetObjectBufferivATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetObjectParameterfvARB(GLhandleARB _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetObjectParameterfvARB,glGetObjectParameterfvARB(_p0,_p1,_p2))
    glCalls().glGetObjectParameterfvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetObjectParameterfvARB,glGetObjectParameterfvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetObjectParameterivARB(GLhandleARB _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetObjectParameterivARB,glGetObjectParameterivARB(_p0,_p1,_p2))
    glCalls().glGetObjectParameterivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetObjectParameterivARB,glGetObjectParameterivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetOcclusionQueryivNV(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetOcclusionQueryivNV,glGetOcclusionQueryivNV(_p0,_p1,_p2))
    glCalls().glGetOcclusionQueryivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetOcclusionQueryivNV,glGetOcclusionQueryivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetOcclusionQueryuivNV(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetOcclusionQueryuivNV,glGetOcclusionQueryuivNV(_p0,_p1,_p2))
    glCalls().glGetOcclusionQueryuivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetOcclusionQueryuivNV,glGetOcclusionQueryuivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetPerfMonitorCounterDataAMD(GLuint _p0, GLenum _p1, GLsizei _p2, GLuint *_p3, GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorCounterDataAMD,glGetPerfMonitorCounterDataAMD(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetPerfMonitorCounterDataAMD(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetPerfMonitorCounterDataAMD,glGetPerfMonitorCounterDataAMD(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetPerfMonitorCounterInfoAMD(GLuint _p0, GLuint _p1, GLenum _p2, void *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorCounterInfoAMD,glGetPerfMonitorCounterInfoAMD(_p0,_p1,_p2,_p3))
    glCalls().glGetPerfMonitorCounterInfoAMD(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetPerfMonitorCounterInfoAMD,glGetPerfMonitorCounterInfoAMD(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetPerfMonitorCounterStringAMD(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLchar *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorCounterStringAMD,glGetPerfMonitorCounterStringAMD(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetPerfMonitorCounterStringAMD(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetPerfMonitorCounterStringAMD,glGetPerfMonitorCounterStringAMD(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetPerfMonitorCountersAMD(GLuint _p0, GLint *_p1, GLint *_p2, GLsizei _p3, GLuint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorCountersAMD,glGetPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetPerfMonitorCountersAMD,glGetPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetPerfMonitorGroupStringAMD(GLuint _p0, GLsizei _p1, GLsizei *_p2, GLchar *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorGroupStringAMD,glGetPerfMonitorGroupStringAMD(_p0,_p1,_p2,_p3))
    glCalls().glGetPerfMonitorGroupStringAMD(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetPerfMonitorGroupStringAMD,glGetPerfMonitorGroupStringAMD(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetPerfMonitorGroupsAMD(GLint *_p0, GLsizei _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetPerfMonitorGroupsAMD,glGetPerfMonitorGroupsAMD(_p0,_p1,_p2))
    glCalls().glGetPerfMonitorGroupsAMD(_p0,_p1,_p2);
    POST_USER_CALL(glGetPerfMonitorGroupsAMD,glGetPerfMonitorGroupsAMD(_p0,_p1,_p2))
}

void GLAPIENTRY glGetPixelMapfv(GLenum map, GLfloat *values)
{
    gli().init();
    PREV_USER_CALL(glGetPixelMapfv,glGetPixelMapfv(map,values))
    glCalls().glGetPixelMapfv(map,values);
    POST_USER_CALL(glGetPixelMapfv,glGetPixelMapfv(map,values))
}

void GLAPIENTRY glGetPixelMapuiv(GLenum map, GLuint *values)
{
    gli().init();
    PREV_USER_CALL(glGetPixelMapuiv,glGetPixelMapuiv(map,values))
    glCalls().glGetPixelMapuiv(map,values);
    POST_USER_CALL(glGetPixelMapuiv,glGetPixelMapuiv(map,values))
}

void GLAPIENTRY glGetPixelMapusv(GLenum map, GLushort *values)
{
    gli().init();
    PREV_USER_CALL(glGetPixelMapusv,glGetPixelMapusv(map,values))
    glCalls().glGetPixelMapusv(map,values);
    POST_USER_CALL(glGetPixelMapusv,glGetPixelMapusv(map,values))
}

void GLAPIENTRY glGetPixelTexGenParameterfvSGIS(GLenum _p0, GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetPixelTexGenParameterfvSGIS,glGetPixelTexGenParameterfvSGIS(_p0,_p1))
    glCalls().glGetPixelTexGenParameterfvSGIS(_p0,_p1);
    POST_USER_CALL(glGetPixelTexGenParameterfvSGIS,glGetPixelTexGenParameterfvSGIS(_p0,_p1))
}

void GLAPIENTRY glGetPixelTexGenParameterivSGIS(GLenum _p0, GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetPixelTexGenParameterivSGIS,glGetPixelTexGenParameterivSGIS(_p0,_p1))
    glCalls().glGetPixelTexGenParameterivSGIS(_p0,_p1);
    POST_USER_CALL(glGetPixelTexGenParameterivSGIS,glGetPixelTexGenParameterivSGIS(_p0,_p1))
}

void GLAPIENTRY glGetPointerIndexedvEXT(GLenum _p0, GLuint _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetPointerIndexedvEXT,glGetPointerIndexedvEXT(_p0,_p1,_p2))
    glCalls().glGetPointerIndexedvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetPointerIndexedvEXT,glGetPointerIndexedvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetPointerv(GLenum pname, GLvoid **params)
{
    gli().init();
    PREV_USER_CALL(glGetPointerv,glGetPointerv(pname,params))
    glCalls().glGetPointerv(pname,params);
    POST_USER_CALL(glGetPointerv,glGetPointerv(pname,params))
}

void GLAPIENTRY glGetPointervEXT(GLenum _p0, GLvoid **_p1)
{
    gli().init();
    PREV_USER_CALL(glGetPointervEXT,glGetPointervEXT(_p0,_p1))
    glCalls().glGetPointervEXT(_p0,_p1);
    POST_USER_CALL(glGetPointervEXT,glGetPointervEXT(_p0,_p1))
}

void GLAPIENTRY glGetPolygonStipple(GLubyte *mask)
{
    gli().init();
    PREV_USER_CALL(glGetPolygonStipple,glGetPolygonStipple(mask))
    glCalls().glGetPolygonStipple(mask);
    POST_USER_CALL(glGetPolygonStipple,glGetPolygonStipple(mask))
}

void GLAPIENTRY glGetProgramEnvParameterIivNV(GLenum _p0, GLuint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramEnvParameterIivNV,glGetProgramEnvParameterIivNV(_p0,_p1,_p2))
    glCalls().glGetProgramEnvParameterIivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramEnvParameterIivNV,glGetProgramEnvParameterIivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramEnvParameterIuivNV(GLenum _p0, GLuint _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramEnvParameterIuivNV,glGetProgramEnvParameterIuivNV(_p0,_p1,_p2))
    glCalls().glGetProgramEnvParameterIuivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramEnvParameterIuivNV,glGetProgramEnvParameterIuivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramEnvParameterdvARB(GLenum _p0, GLuint _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramEnvParameterdvARB,glGetProgramEnvParameterdvARB(_p0,_p1,_p2))
    glCalls().glGetProgramEnvParameterdvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramEnvParameterdvARB,glGetProgramEnvParameterdvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramEnvParameterfvARB(GLenum _p0, GLuint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramEnvParameterfvARB,glGetProgramEnvParameterfvARB(_p0,_p1,_p2))
    glCalls().glGetProgramEnvParameterfvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramEnvParameterfvARB,glGetProgramEnvParameterfvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramInfoLog(GLuint _p0, GLsizei _p1, GLsizei *_p2, GLchar *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetProgramInfoLog,glGetProgramInfoLog(_p0,_p1,_p2,_p3))
    glCalls().glGetProgramInfoLog(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetProgramInfoLog,glGetProgramInfoLog(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetProgramLocalParameterIivNV(GLenum _p0, GLuint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramLocalParameterIivNV,glGetProgramLocalParameterIivNV(_p0,_p1,_p2))
    glCalls().glGetProgramLocalParameterIivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramLocalParameterIivNV,glGetProgramLocalParameterIivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramLocalParameterIuivNV(GLenum _p0, GLuint _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramLocalParameterIuivNV,glGetProgramLocalParameterIuivNV(_p0,_p1,_p2))
    glCalls().glGetProgramLocalParameterIuivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramLocalParameterIuivNV,glGetProgramLocalParameterIuivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramLocalParameterdvARB(GLenum _p0, GLuint _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramLocalParameterdvARB,glGetProgramLocalParameterdvARB(_p0,_p1,_p2))
    glCalls().glGetProgramLocalParameterdvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramLocalParameterdvARB,glGetProgramLocalParameterdvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramLocalParameterfvARB(GLenum _p0, GLuint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramLocalParameterfvARB,glGetProgramLocalParameterfvARB(_p0,_p1,_p2))
    glCalls().glGetProgramLocalParameterfvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramLocalParameterfvARB,glGetProgramLocalParameterfvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramNamedParameterdvNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetProgramNamedParameterdvNV,glGetProgramNamedParameterdvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetProgramNamedParameterdvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetProgramNamedParameterdvNV,glGetProgramNamedParameterdvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetProgramNamedParameterfvNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetProgramNamedParameterfvNV,glGetProgramNamedParameterfvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetProgramNamedParameterfvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetProgramNamedParameterfvNV,glGetProgramNamedParameterfvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetProgramParameterdvNV(GLenum _p0, GLuint _p1, GLenum _p2, GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetProgramParameterdvNV,glGetProgramParameterdvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetProgramParameterdvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetProgramParameterdvNV,glGetProgramParameterdvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetProgramParameterfvNV(GLenum _p0, GLuint _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetProgramParameterfvNV,glGetProgramParameterfvNV(_p0,_p1,_p2,_p3))
    glCalls().glGetProgramParameterfvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetProgramParameterfvNV,glGetProgramParameterfvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetProgramStringARB(GLenum _p0, GLenum _p1, GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramStringARB,glGetProgramStringARB(_p0,_p1,_p2))
    glCalls().glGetProgramStringARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramStringARB,glGetProgramStringARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramStringNV(GLuint _p0, GLenum _p1, GLubyte *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramStringNV,glGetProgramStringNV(_p0,_p1,_p2))
    glCalls().glGetProgramStringNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramStringNV,glGetProgramStringNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramiv(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramiv,glGetProgramiv(_p0,_p1,_p2))
    glCalls().glGetProgramiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramiv,glGetProgramiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramivARB(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramivARB,glGetProgramivARB(_p0,_p1,_p2))
    glCalls().glGetProgramivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramivARB,glGetProgramivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetProgramivNV(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetProgramivNV,glGetProgramivNV(_p0,_p1,_p2))
    glCalls().glGetProgramivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetProgramivNV,glGetProgramivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjecti64vEXT(GLuint _p0, GLenum _p1, GLint64EXT *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjecti64vEXT,glGetQueryObjecti64vEXT(_p0,_p1,_p2))
    glCalls().glGetQueryObjecti64vEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjecti64vEXT,glGetQueryObjecti64vEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjectiv(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjectiv,glGetQueryObjectiv(_p0,_p1,_p2))
    glCalls().glGetQueryObjectiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjectiv,glGetQueryObjectiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjectivARB(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjectivARB,glGetQueryObjectivARB(_p0,_p1,_p2))
    glCalls().glGetQueryObjectivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjectivARB,glGetQueryObjectivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjectui64vEXT(GLuint _p0, GLenum _p1, GLuint64EXT *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjectui64vEXT,glGetQueryObjectui64vEXT(_p0,_p1,_p2))
    glCalls().glGetQueryObjectui64vEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjectui64vEXT,glGetQueryObjectui64vEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjectuiv(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjectuiv,glGetQueryObjectuiv(_p0,_p1,_p2))
    glCalls().glGetQueryObjectuiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjectuiv,glGetQueryObjectuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryObjectuivARB(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryObjectuivARB,glGetQueryObjectuivARB(_p0,_p1,_p2))
    glCalls().glGetQueryObjectuivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryObjectuivARB,glGetQueryObjectuivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryiv(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryiv,glGetQueryiv(_p0,_p1,_p2))
    glCalls().glGetQueryiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryiv,glGetQueryiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetQueryivARB(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetQueryivARB,glGetQueryivARB(_p0,_p1,_p2))
    glCalls().glGetQueryivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetQueryivARB,glGetQueryivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetRenderbufferParameteriv(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetRenderbufferParameteriv,glGetRenderbufferParameteriv(_p0,_p1,_p2))
    glCalls().glGetRenderbufferParameteriv(_p0,_p1,_p2);
    POST_USER_CALL(glGetRenderbufferParameteriv,glGetRenderbufferParameteriv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetRenderbufferParameterivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetRenderbufferParameterivEXT,glGetRenderbufferParameterivEXT(_p0,_p1,_p2))
    glCalls().glGetRenderbufferParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetRenderbufferParameterivEXT,glGetRenderbufferParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetSeparableFilter(GLenum target, GLenum format, GLenum type, GLvoid *row, GLvoid *column, GLvoid *span)
{
    gli().init();
    PREV_USER_CALL(glGetSeparableFilter,glGetSeparableFilter(target,format,type,row,column,span))
    glCalls().glGetSeparableFilter(target,format,type,row,column,span);
    POST_USER_CALL(glGetSeparableFilter,glGetSeparableFilter(target,format,type,row,column,span))
}

void GLAPIENTRY glGetSeparableFilterEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLvoid *_p3, GLvoid *_p4, GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glGetSeparableFilterEXT,glGetSeparableFilterEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glGetSeparableFilterEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glGetSeparableFilterEXT,glGetSeparableFilterEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glGetShaderInfoLog(GLuint _p0, GLsizei _p1, GLsizei *_p2, GLchar *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetShaderInfoLog,glGetShaderInfoLog(_p0,_p1,_p2,_p3))
    glCalls().glGetShaderInfoLog(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetShaderInfoLog,glGetShaderInfoLog(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetShaderSource(GLuint _p0, GLsizei _p1, GLsizei *_p2, GLchar *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetShaderSource,glGetShaderSource(_p0,_p1,_p2,_p3))
    glCalls().glGetShaderSource(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetShaderSource,glGetShaderSource(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetShaderSourceARB(GLhandleARB _p0, GLsizei _p1, GLsizei *_p2, GLcharARB *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetShaderSourceARB,glGetShaderSourceARB(_p0,_p1,_p2,_p3))
    glCalls().glGetShaderSourceARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetShaderSourceARB,glGetShaderSourceARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetShaderiv(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetShaderiv,glGetShaderiv(_p0,_p1,_p2))
    glCalls().glGetShaderiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetShaderiv,glGetShaderiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetSharpenTexFuncSGIS(GLenum _p0, GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetSharpenTexFuncSGIS,glGetSharpenTexFuncSGIS(_p0,_p1))
    glCalls().glGetSharpenTexFuncSGIS(_p0,_p1);
    POST_USER_CALL(glGetSharpenTexFuncSGIS,glGetSharpenTexFuncSGIS(_p0,_p1))
}

const GLubyte * GLAPIENTRY glGetString(GLenum name)
{
    gli().init();
    const GLubyte *_result;
    PREV_USER_CALL(glGetString,glGetString(name))
    _result = glCalls().glGetString(name);
    POST_USER_CALL(glGetString,glGetString(name))
    return _result;
}

const GLubyte * GLAPIENTRY glGetStringi(GLenum _p0, GLuint _p1)
{
    gli().init();
    const GLubyte *_result;
    PREV_USER_CALL(glGetStringi,glGetStringi(_p0,_p1))
    _result = glCalls().glGetStringi(_p0,_p1);
    POST_USER_CALL(glGetStringi,glGetStringi(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetTexBumpParameterfvATI(GLenum _p0, GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetTexBumpParameterfvATI,glGetTexBumpParameterfvATI(_p0,_p1))
    glCalls().glGetTexBumpParameterfvATI(_p0,_p1);
    POST_USER_CALL(glGetTexBumpParameterfvATI,glGetTexBumpParameterfvATI(_p0,_p1))
}

void GLAPIENTRY glGetTexBumpParameterivATI(GLenum _p0, GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glGetTexBumpParameterivATI,glGetTexBumpParameterivATI(_p0,_p1))
    glCalls().glGetTexBumpParameterivATI(_p0,_p1);
    POST_USER_CALL(glGetTexBumpParameterivATI,glGetTexBumpParameterivATI(_p0,_p1))
}

void GLAPIENTRY glGetTexEnvfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexEnvfv,glGetTexEnvfv(target,pname,params))
    glCalls().glGetTexEnvfv(target,pname,params);
    POST_USER_CALL(glGetTexEnvfv,glGetTexEnvfv(target,pname,params))
}

void GLAPIENTRY glGetTexEnviv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexEnviv,glGetTexEnviv(target,pname,params))
    glCalls().glGetTexEnviv(target,pname,params);
    POST_USER_CALL(glGetTexEnviv,glGetTexEnviv(target,pname,params))
}

void GLAPIENTRY glGetTexFilterFuncSGIS(GLenum _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTexFilterFuncSGIS,glGetTexFilterFuncSGIS(_p0,_p1,_p2))
    glCalls().glGetTexFilterFuncSGIS(_p0,_p1,_p2);
    POST_USER_CALL(glGetTexFilterFuncSGIS,glGetTexFilterFuncSGIS(_p0,_p1,_p2))
}

void GLAPIENTRY glGetTexGendv(GLenum coord, GLenum pname, GLdouble *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexGendv,glGetTexGendv(coord,pname,params))
    glCalls().glGetTexGendv(coord,pname,params);
    POST_USER_CALL(glGetTexGendv,glGetTexGendv(coord,pname,params))
}

void GLAPIENTRY glGetTexGenfv(GLenum coord, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexGenfv,glGetTexGenfv(coord,pname,params))
    glCalls().glGetTexGenfv(coord,pname,params);
    POST_USER_CALL(glGetTexGenfv,glGetTexGenfv(coord,pname,params))
}

void GLAPIENTRY glGetTexGeniv(GLenum coord, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexGeniv,glGetTexGeniv(coord,pname,params))
    glCalls().glGetTexGeniv(coord,pname,params);
    POST_USER_CALL(glGetTexGeniv,glGetTexGeniv(coord,pname,params))
}

void GLAPIENTRY glGetTexImage(GLenum target, GLint level, GLenum format, GLenum type, GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glGetTexImage,glGetTexImage(target,level,format,type,pixels))
    glCalls().glGetTexImage(target,level,format,type,pixels);
    POST_USER_CALL(glGetTexImage,glGetTexImage(target,level,format,type,pixels))
}

void GLAPIENTRY glGetTexLevelParameterfv(GLenum target, GLint level, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexLevelParameterfv,glGetTexLevelParameterfv(target,level,pname,params))
    glCalls().glGetTexLevelParameterfv(target,level,pname,params);
    POST_USER_CALL(glGetTexLevelParameterfv,glGetTexLevelParameterfv(target,level,pname,params))
}

void GLAPIENTRY glGetTexLevelParameteriv(GLenum target, GLint level, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexLevelParameteriv,glGetTexLevelParameteriv(target,level,pname,params))
    glCalls().glGetTexLevelParameteriv(target,level,pname,params);
    POST_USER_CALL(glGetTexLevelParameteriv,glGetTexLevelParameteriv(target,level,pname,params))
}

void GLAPIENTRY glGetTexParameterIiv(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameterIiv,glGetTexParameterIiv(_p0,_p1,_p2))
    glCalls().glGetTexParameterIiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetTexParameterIiv,glGetTexParameterIiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetTexParameterIivEXT(GLenum _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameterIivEXT,glGetTexParameterIivEXT(_p0,_p1,_p2))
    glCalls().glGetTexParameterIivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetTexParameterIivEXT,glGetTexParameterIivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetTexParameterIuiv(GLenum _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameterIuiv,glGetTexParameterIuiv(_p0,_p1,_p2))
    glCalls().glGetTexParameterIuiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetTexParameterIuiv,glGetTexParameterIuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetTexParameterIuivEXT(GLenum _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameterIuivEXT,glGetTexParameterIuivEXT(_p0,_p1,_p2))
    glCalls().glGetTexParameterIuivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetTexParameterIuivEXT,glGetTexParameterIuivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetTexParameterfv(GLenum target, GLenum pname, GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameterfv,glGetTexParameterfv(target,pname,params))
    glCalls().glGetTexParameterfv(target,pname,params);
    POST_USER_CALL(glGetTexParameterfv,glGetTexParameterfv(target,pname,params))
}

void GLAPIENTRY glGetTexParameteriv(GLenum target, GLenum pname, GLint *params)
{
    gli().init();
    PREV_USER_CALL(glGetTexParameteriv,glGetTexParameteriv(target,pname,params))
    glCalls().glGetTexParameteriv(target,pname,params);
    POST_USER_CALL(glGetTexParameteriv,glGetTexParameteriv(target,pname,params))
}

void GLAPIENTRY glGetTextureImageEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLenum _p4, GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glGetTextureImageEXT,glGetTextureImageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glGetTextureImageEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glGetTextureImageEXT,glGetTextureImageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glGetTextureLevelParameterfvEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetTextureLevelParameterfvEXT,glGetTextureLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetTextureLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetTextureLevelParameterfvEXT,glGetTextureLevelParameterfvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetTextureLevelParameterivEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glGetTextureLevelParameterivEXT,glGetTextureLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glGetTextureLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glGetTextureLevelParameterivEXT,glGetTextureLevelParameterivEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glGetTextureParameterIivEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetTextureParameterIivEXT,glGetTextureParameterIivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetTextureParameterIivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetTextureParameterIivEXT,glGetTextureParameterIivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetTextureParameterIuivEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetTextureParameterIuivEXT,glGetTextureParameterIuivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetTextureParameterIuivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetTextureParameterIuivEXT,glGetTextureParameterIuivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetTextureParameterfvEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetTextureParameterfvEXT,glGetTextureParameterfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetTextureParameterfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetTextureParameterfvEXT,glGetTextureParameterfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetTextureParameterivEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetTextureParameterivEXT,glGetTextureParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glGetTextureParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetTextureParameterivEXT,glGetTextureParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetTrackMatrixivNV(GLenum _p0, GLuint _p1, GLenum _p2, GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetTrackMatrixivNV,glGetTrackMatrixivNV(_p0,_p1,_p2,_p3))
    glCalls().glGetTrackMatrixivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetTrackMatrixivNV,glGetTrackMatrixivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glGetTransformFeedbackVarying(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLsizei *_p4, GLenum *_p5, GLchar *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetTransformFeedbackVarying,glGetTransformFeedbackVarying(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetTransformFeedbackVarying(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetTransformFeedbackVarying,glGetTransformFeedbackVarying(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetTransformFeedbackVaryingEXT(GLuint _p0, GLuint _p1, GLsizei _p2, GLsizei *_p3, GLsizei *_p4, GLenum *_p5, GLchar *_p6)
{
    gli().init();
    PREV_USER_CALL(glGetTransformFeedbackVaryingEXT,glGetTransformFeedbackVaryingEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glGetTransformFeedbackVaryingEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glGetTransformFeedbackVaryingEXT,glGetTransformFeedbackVaryingEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glGetTransformFeedbackVaryingNV(GLuint _p0, GLuint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetTransformFeedbackVaryingNV,glGetTransformFeedbackVaryingNV(_p0,_p1,_p2))
    glCalls().glGetTransformFeedbackVaryingNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetTransformFeedbackVaryingNV,glGetTransformFeedbackVaryingNV(_p0,_p1,_p2))
}

GLuint GLAPIENTRY glGetUniformBlockIndex(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glGetUniformBlockIndex,glGetUniformBlockIndex(_p0,_p1))
    _result = glCalls().glGetUniformBlockIndex(_p0,_p1);
    POST_USER_CALL(glGetUniformBlockIndex,glGetUniformBlockIndex(_p0,_p1))
    return _result;
}

GLint GLAPIENTRY glGetUniformBufferSizeEXT(GLuint _p0, GLint _p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetUniformBufferSizeEXT,glGetUniformBufferSizeEXT(_p0,_p1))
    _result = glCalls().glGetUniformBufferSizeEXT(_p0,_p1);
    POST_USER_CALL(glGetUniformBufferSizeEXT,glGetUniformBufferSizeEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetUniformIndices(GLuint _p0, GLsizei _p1, const GLchar **_p2, GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glGetUniformIndices,glGetUniformIndices(_p0,_p1,_p2,_p3))
    glCalls().glGetUniformIndices(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glGetUniformIndices,glGetUniformIndices(_p0,_p1,_p2,_p3))
}

GLint GLAPIENTRY glGetUniformLocation(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetUniformLocation,glGetUniformLocation(_p0,_p1))
    _result = glCalls().glGetUniformLocation(_p0,_p1);
    POST_USER_CALL(glGetUniformLocation,glGetUniformLocation(_p0,_p1))
    return _result;
}

GLint GLAPIENTRY glGetUniformLocationARB(GLhandleARB _p0, const GLcharARB *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetUniformLocationARB,glGetUniformLocationARB(_p0,_p1))
    _result = glCalls().glGetUniformLocationARB(_p0,_p1);
    POST_USER_CALL(glGetUniformLocationARB,glGetUniformLocationARB(_p0,_p1))
    return _result;
}

GLintptr GLAPIENTRY glGetUniformOffsetEXT(GLuint _p0, GLint _p1)
{
    gli().init();
    GLintptr _result;
    PREV_USER_CALL(glGetUniformOffsetEXT,glGetUniformOffsetEXT(_p0,_p1))
    _result = glCalls().glGetUniformOffsetEXT(_p0,_p1);
    POST_USER_CALL(glGetUniformOffsetEXT,glGetUniformOffsetEXT(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetUniformfv(GLuint _p0, GLint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformfv,glGetUniformfv(_p0,_p1,_p2))
    glCalls().glGetUniformfv(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformfv,glGetUniformfv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetUniformfvARB(GLhandleARB _p0, GLint _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformfvARB,glGetUniformfvARB(_p0,_p1,_p2))
    glCalls().glGetUniformfvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformfvARB,glGetUniformfvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetUniformiv(GLuint _p0, GLint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformiv,glGetUniformiv(_p0,_p1,_p2))
    glCalls().glGetUniformiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformiv,glGetUniformiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetUniformivARB(GLhandleARB _p0, GLint _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformivARB,glGetUniformivARB(_p0,_p1,_p2))
    glCalls().glGetUniformivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformivARB,glGetUniformivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetUniformuiv(GLuint _p0, GLint _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformuiv,glGetUniformuiv(_p0,_p1,_p2))
    glCalls().glGetUniformuiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformuiv,glGetUniformuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetUniformuivEXT(GLuint _p0, GLint _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetUniformuivEXT,glGetUniformuivEXT(_p0,_p1,_p2))
    glCalls().glGetUniformuivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetUniformuivEXT,glGetUniformuivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantArrayObjectfvATI(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantArrayObjectfvATI,glGetVariantArrayObjectfvATI(_p0,_p1,_p2))
    glCalls().glGetVariantArrayObjectfvATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantArrayObjectfvATI,glGetVariantArrayObjectfvATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantArrayObjectivATI(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantArrayObjectivATI,glGetVariantArrayObjectivATI(_p0,_p1,_p2))
    glCalls().glGetVariantArrayObjectivATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantArrayObjectivATI,glGetVariantArrayObjectivATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantBooleanvEXT(GLuint _p0, GLenum _p1, GLboolean *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantBooleanvEXT,glGetVariantBooleanvEXT(_p0,_p1,_p2))
    glCalls().glGetVariantBooleanvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantBooleanvEXT,glGetVariantBooleanvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantFloatvEXT(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantFloatvEXT,glGetVariantFloatvEXT(_p0,_p1,_p2))
    glCalls().glGetVariantFloatvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantFloatvEXT,glGetVariantFloatvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantIntegervEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantIntegervEXT,glGetVariantIntegervEXT(_p0,_p1,_p2))
    glCalls().glGetVariantIntegervEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantIntegervEXT,glGetVariantIntegervEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVariantPointervEXT(GLuint _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVariantPointervEXT,glGetVariantPointervEXT(_p0,_p1,_p2))
    glCalls().glGetVariantPointervEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVariantPointervEXT,glGetVariantPointervEXT(_p0,_p1,_p2))
}

GLint GLAPIENTRY glGetVaryingLocationNV(GLuint _p0, const GLchar *_p1)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glGetVaryingLocationNV,glGetVaryingLocationNV(_p0,_p1))
    _result = glCalls().glGetVaryingLocationNV(_p0,_p1);
    POST_USER_CALL(glGetVaryingLocationNV,glGetVaryingLocationNV(_p0,_p1))
    return _result;
}

void GLAPIENTRY glGetVertexAttribArrayObjectfvATI(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribArrayObjectfvATI,glGetVertexAttribArrayObjectfvATI(_p0,_p1,_p2))
    glCalls().glGetVertexAttribArrayObjectfvATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribArrayObjectfvATI,glGetVertexAttribArrayObjectfvATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribArrayObjectivATI(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribArrayObjectivATI,glGetVertexAttribArrayObjectivATI(_p0,_p1,_p2))
    glCalls().glGetVertexAttribArrayObjectivATI(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribArrayObjectivATI,glGetVertexAttribArrayObjectivATI(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribIiv(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribIiv,glGetVertexAttribIiv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribIiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribIiv,glGetVertexAttribIiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribIivEXT(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribIivEXT,glGetVertexAttribIivEXT(_p0,_p1,_p2))
    glCalls().glGetVertexAttribIivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribIivEXT,glGetVertexAttribIivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribIuiv(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribIuiv,glGetVertexAttribIuiv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribIuiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribIuiv,glGetVertexAttribIuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribIuivEXT(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribIuivEXT,glGetVertexAttribIuivEXT(_p0,_p1,_p2))
    glCalls().glGetVertexAttribIuivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribIuivEXT,glGetVertexAttribIuivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribPointerv(GLuint _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribPointerv,glGetVertexAttribPointerv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribPointerv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribPointerv,glGetVertexAttribPointerv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribPointervARB(GLuint _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribPointervARB,glGetVertexAttribPointervARB(_p0,_p1,_p2))
    glCalls().glGetVertexAttribPointervARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribPointervARB,glGetVertexAttribPointervARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribPointervNV(GLuint _p0, GLenum _p1, GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribPointervNV,glGetVertexAttribPointervNV(_p0,_p1,_p2))
    glCalls().glGetVertexAttribPointervNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribPointervNV,glGetVertexAttribPointervNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribdv(GLuint _p0, GLenum _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribdv,glGetVertexAttribdv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribdv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribdv,glGetVertexAttribdv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribdvARB(GLuint _p0, GLenum _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribdvARB,glGetVertexAttribdvARB(_p0,_p1,_p2))
    glCalls().glGetVertexAttribdvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribdvARB,glGetVertexAttribdvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribdvNV(GLuint _p0, GLenum _p1, GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribdvNV,glGetVertexAttribdvNV(_p0,_p1,_p2))
    glCalls().glGetVertexAttribdvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribdvNV,glGetVertexAttribdvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribfv(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribfv,glGetVertexAttribfv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribfv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribfv,glGetVertexAttribfv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribfvARB(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribfvARB,glGetVertexAttribfvARB(_p0,_p1,_p2))
    glCalls().glGetVertexAttribfvARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribfvARB,glGetVertexAttribfvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribfvNV(GLuint _p0, GLenum _p1, GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribfvNV,glGetVertexAttribfvNV(_p0,_p1,_p2))
    glCalls().glGetVertexAttribfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribfvNV,glGetVertexAttribfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribiv(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribiv,glGetVertexAttribiv(_p0,_p1,_p2))
    glCalls().glGetVertexAttribiv(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribiv,glGetVertexAttribiv(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribivARB(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribivARB,glGetVertexAttribivARB(_p0,_p1,_p2))
    glCalls().glGetVertexAttribivARB(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribivARB,glGetVertexAttribivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVertexAttribivNV(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVertexAttribivNV,glGetVertexAttribivNV(_p0,_p1,_p2))
    glCalls().glGetVertexAttribivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVertexAttribivNV,glGetVertexAttribivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVideoi64vNV(GLuint _p0, GLenum _p1, GLint64EXT *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVideoi64vNV,glGetVideoi64vNV(_p0,_p1,_p2))
    glCalls().glGetVideoi64vNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVideoi64vNV,glGetVideoi64vNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVideoivNV(GLuint _p0, GLenum _p1, GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVideoivNV,glGetVideoivNV(_p0,_p1,_p2))
    glCalls().glGetVideoivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVideoivNV,glGetVideoivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVideoui64vNV(GLuint _p0, GLenum _p1, GLuint64EXT *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVideoui64vNV,glGetVideoui64vNV(_p0,_p1,_p2))
    glCalls().glGetVideoui64vNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVideoui64vNV,glGetVideoui64vNV(_p0,_p1,_p2))
}

void GLAPIENTRY glGetVideouivNV(GLuint _p0, GLenum _p1, GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glGetVideouivNV,glGetVideouivNV(_p0,_p1,_p2))
    glCalls().glGetVideouivNV(_p0,_p1,_p2);
    POST_USER_CALL(glGetVideouivNV,glGetVideouivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glHint(GLenum target, GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glHint,glHint(target,mode))
    glCalls().glHint(target,mode);
    POST_USER_CALL(glHint,glHint(target,mode))
}

void GLAPIENTRY glHintPGI(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glHintPGI,glHintPGI(_p0,_p1))
    glCalls().glHintPGI(_p0,_p1);
    POST_USER_CALL(glHintPGI,glHintPGI(_p0,_p1))
}

void GLAPIENTRY glHistogram(GLenum target, GLsizei width, GLenum internalformat, GLboolean sink)
{
    gli().init();
    PREV_USER_CALL(glHistogram,glHistogram(target,width,internalformat,sink))
    glCalls().glHistogram(target,width,internalformat,sink);
    POST_USER_CALL(glHistogram,glHistogram(target,width,internalformat,sink))
}

void GLAPIENTRY glHistogramEXT(GLenum _p0, GLsizei _p1, GLenum _p2, GLboolean _p3)
{
    gli().init();
    PREV_USER_CALL(glHistogramEXT,glHistogramEXT(_p0,_p1,_p2,_p3))
    glCalls().glHistogramEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glHistogramEXT,glHistogramEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glIglooInterfaceSGIX(GLenum _p0, const GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glIglooInterfaceSGIX,glIglooInterfaceSGIX(_p0,_p1))
    glCalls().glIglooInterfaceSGIX(_p0,_p1);
    POST_USER_CALL(glIglooInterfaceSGIX,glIglooInterfaceSGIX(_p0,_p1))
}

void GLAPIENTRY glImageTransformParameterfHP(GLenum _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glImageTransformParameterfHP,glImageTransformParameterfHP(_p0,_p1,_p2))
    glCalls().glImageTransformParameterfHP(_p0,_p1,_p2);
    POST_USER_CALL(glImageTransformParameterfHP,glImageTransformParameterfHP(_p0,_p1,_p2))
}

void GLAPIENTRY glImageTransformParameterfvHP(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glImageTransformParameterfvHP,glImageTransformParameterfvHP(_p0,_p1,_p2))
    glCalls().glImageTransformParameterfvHP(_p0,_p1,_p2);
    POST_USER_CALL(glImageTransformParameterfvHP,glImageTransformParameterfvHP(_p0,_p1,_p2))
}

void GLAPIENTRY glImageTransformParameteriHP(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glImageTransformParameteriHP,glImageTransformParameteriHP(_p0,_p1,_p2))
    glCalls().glImageTransformParameteriHP(_p0,_p1,_p2);
    POST_USER_CALL(glImageTransformParameteriHP,glImageTransformParameteriHP(_p0,_p1,_p2))
}

void GLAPIENTRY glImageTransformParameterivHP(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glImageTransformParameterivHP,glImageTransformParameterivHP(_p0,_p1,_p2))
    glCalls().glImageTransformParameterivHP(_p0,_p1,_p2);
    POST_USER_CALL(glImageTransformParameterivHP,glImageTransformParameterivHP(_p0,_p1,_p2))
}

void GLAPIENTRY glIndexFuncEXT(GLenum _p0, GLclampf _p1)
{
    gli().init();
    PREV_USER_CALL(glIndexFuncEXT,glIndexFuncEXT(_p0,_p1))
    glCalls().glIndexFuncEXT(_p0,_p1);
    POST_USER_CALL(glIndexFuncEXT,glIndexFuncEXT(_p0,_p1))
}

void GLAPIENTRY glIndexMask(GLuint mask)
{
    gli().init();
    PREV_USER_CALL(glIndexMask,glIndexMask(mask))
    glCalls().glIndexMask(mask);
    POST_USER_CALL(glIndexMask,glIndexMask(mask))
}

void GLAPIENTRY glIndexMaterialEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glIndexMaterialEXT,glIndexMaterialEXT(_p0,_p1))
    glCalls().glIndexMaterialEXT(_p0,_p1);
    POST_USER_CALL(glIndexMaterialEXT,glIndexMaterialEXT(_p0,_p1))
}

void GLAPIENTRY glIndexPointer(GLenum type, GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glIndexPointer,glIndexPointer(type,stride,ptr))
    glCalls().glIndexPointer(type,stride,ptr);
    POST_USER_CALL(glIndexPointer,glIndexPointer(type,stride,ptr))
}

void GLAPIENTRY glIndexPointerEXT(GLenum _p0, GLsizei _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glIndexPointerEXT,glIndexPointerEXT(_p0,_p1,_p2,_p3))
    glCalls().glIndexPointerEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glIndexPointerEXT,glIndexPointerEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glIndexd(GLdouble c)
{
    gli().init();
    PREV_USER_CALL(glIndexd,glIndexd(c))
    glCalls().glIndexd(c);
    POST_USER_CALL(glIndexd,glIndexd(c))
}

void GLAPIENTRY glIndexdv(const GLdouble *c)
{
    gli().init();
    PREV_USER_CALL(glIndexdv,glIndexdv(c))
    glCalls().glIndexdv(c);
    POST_USER_CALL(glIndexdv,glIndexdv(c))
}

void GLAPIENTRY glIndexf(GLfloat c)
{
    gli().init();
    PREV_USER_CALL(glIndexf,glIndexf(c))
    glCalls().glIndexf(c);
    POST_USER_CALL(glIndexf,glIndexf(c))
}

void GLAPIENTRY glIndexfv(const GLfloat *c)
{
    gli().init();
    PREV_USER_CALL(glIndexfv,glIndexfv(c))
    glCalls().glIndexfv(c);
    POST_USER_CALL(glIndexfv,glIndexfv(c))
}

void GLAPIENTRY glIndexi(GLint c)
{
    gli().init();
    PREV_USER_CALL(glIndexi,glIndexi(c))
    glCalls().glIndexi(c);
    POST_USER_CALL(glIndexi,glIndexi(c))
}

void GLAPIENTRY glIndexiv(const GLint *c)
{
    gli().init();
    PREV_USER_CALL(glIndexiv,glIndexiv(c))
    glCalls().glIndexiv(c);
    POST_USER_CALL(glIndexiv,glIndexiv(c))
}

void GLAPIENTRY glIndexs(GLshort c)
{
    gli().init();
    PREV_USER_CALL(glIndexs,glIndexs(c))
    glCalls().glIndexs(c);
    POST_USER_CALL(glIndexs,glIndexs(c))
}

void GLAPIENTRY glIndexsv(const GLshort *c)
{
    gli().init();
    PREV_USER_CALL(glIndexsv,glIndexsv(c))
    glCalls().glIndexsv(c);
    POST_USER_CALL(glIndexsv,glIndexsv(c))
}

void GLAPIENTRY glIndexub(GLubyte c)
{
    gli().init();
    PREV_USER_CALL(glIndexub,glIndexub(c))
    glCalls().glIndexub(c);
    POST_USER_CALL(glIndexub,glIndexub(c))
}

void GLAPIENTRY glIndexubv(const GLubyte *c)
{
    gli().init();
    PREV_USER_CALL(glIndexubv,glIndexubv(c))
    glCalls().glIndexubv(c);
    POST_USER_CALL(glIndexubv,glIndexubv(c))
}

void GLAPIENTRY glInitNames()
{
    gli().init();
    PREV_USER_CALL(glInitNames,glInitNames())
    glCalls().glInitNames();
    POST_USER_CALL(glInitNames,glInitNames())
}

void GLAPIENTRY glInsertComponentEXT(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glInsertComponentEXT,glInsertComponentEXT(_p0,_p1,_p2))
    glCalls().glInsertComponentEXT(_p0,_p1,_p2);
    POST_USER_CALL(glInsertComponentEXT,glInsertComponentEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glInstrumentsBufferSGIX(GLsizei _p0, GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glInstrumentsBufferSGIX,glInstrumentsBufferSGIX(_p0,_p1))
    glCalls().glInstrumentsBufferSGIX(_p0,_p1);
    POST_USER_CALL(glInstrumentsBufferSGIX,glInstrumentsBufferSGIX(_p0,_p1))
}

void GLAPIENTRY glInterleavedArrays(GLenum format, GLsizei stride, const GLvoid *pointer)
{
    gli().init();
    PREV_USER_CALL(glInterleavedArrays,glInterleavedArrays(format,stride,pointer))
    glCalls().glInterleavedArrays(format,stride,pointer);
    POST_USER_CALL(glInterleavedArrays,glInterleavedArrays(format,stride,pointer))
}

GLboolean GLAPIENTRY glIsAsyncMarkerSGIX(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsAsyncMarkerSGIX,glIsAsyncMarkerSGIX(_p0))
    _result = glCalls().glIsAsyncMarkerSGIX(_p0);
    POST_USER_CALL(glIsAsyncMarkerSGIX,glIsAsyncMarkerSGIX(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsBuffer(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsBuffer,glIsBuffer(_p0))
    _result = glCalls().glIsBuffer(_p0);
    POST_USER_CALL(glIsBuffer,glIsBuffer(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsBufferARB(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsBufferARB,glIsBufferARB(_p0))
    _result = glCalls().glIsBufferARB(_p0);
    POST_USER_CALL(glIsBufferARB,glIsBufferARB(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsEnabled(GLenum cap)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsEnabled,glIsEnabled(cap))
    _result = glCalls().glIsEnabled(cap);
    POST_USER_CALL(glIsEnabled,glIsEnabled(cap))
    return _result;
}

GLboolean GLAPIENTRY glIsEnabledIndexedEXT(GLenum _p0, GLuint _p1)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsEnabledIndexedEXT,glIsEnabledIndexedEXT(_p0,_p1))
    _result = glCalls().glIsEnabledIndexedEXT(_p0,_p1);
    POST_USER_CALL(glIsEnabledIndexedEXT,glIsEnabledIndexedEXT(_p0,_p1))
    return _result;
}

GLboolean GLAPIENTRY glIsEnabledi(GLenum _p0, GLuint _p1)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsEnabledi,glIsEnabledi(_p0,_p1))
    _result = glCalls().glIsEnabledi(_p0,_p1);
    POST_USER_CALL(glIsEnabledi,glIsEnabledi(_p0,_p1))
    return _result;
}

GLboolean GLAPIENTRY glIsFenceAPPLE(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsFenceAPPLE,glIsFenceAPPLE(_p0))
    _result = glCalls().glIsFenceAPPLE(_p0);
    POST_USER_CALL(glIsFenceAPPLE,glIsFenceAPPLE(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsFenceNV(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsFenceNV,glIsFenceNV(_p0))
    _result = glCalls().glIsFenceNV(_p0);
    POST_USER_CALL(glIsFenceNV,glIsFenceNV(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsFramebuffer(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsFramebuffer,glIsFramebuffer(_p0))
    _result = glCalls().glIsFramebuffer(_p0);
    POST_USER_CALL(glIsFramebuffer,glIsFramebuffer(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsFramebufferEXT(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsFramebufferEXT,glIsFramebufferEXT(_p0))
    _result = glCalls().glIsFramebufferEXT(_p0);
    POST_USER_CALL(glIsFramebufferEXT,glIsFramebufferEXT(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsList(GLuint list)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsList,glIsList(list))
    _result = glCalls().glIsList(list);
    POST_USER_CALL(glIsList,glIsList(list))
    return _result;
}

GLboolean GLAPIENTRY glIsObjectBufferATI(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsObjectBufferATI,glIsObjectBufferATI(_p0))
    _result = glCalls().glIsObjectBufferATI(_p0);
    POST_USER_CALL(glIsObjectBufferATI,glIsObjectBufferATI(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsOcclusionQueryNV(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsOcclusionQueryNV,glIsOcclusionQueryNV(_p0))
    _result = glCalls().glIsOcclusionQueryNV(_p0);
    POST_USER_CALL(glIsOcclusionQueryNV,glIsOcclusionQueryNV(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsProgram(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsProgram,glIsProgram(_p0))
    _result = glCalls().glIsProgram(_p0);
    POST_USER_CALL(glIsProgram,glIsProgram(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsProgramARB(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsProgramARB,glIsProgramARB(_p0))
    _result = glCalls().glIsProgramARB(_p0);
    POST_USER_CALL(glIsProgramARB,glIsProgramARB(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsProgramNV(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsProgramNV,glIsProgramNV(_p0))
    _result = glCalls().glIsProgramNV(_p0);
    POST_USER_CALL(glIsProgramNV,glIsProgramNV(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsQuery(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsQuery,glIsQuery(_p0))
    _result = glCalls().glIsQuery(_p0);
    POST_USER_CALL(glIsQuery,glIsQuery(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsQueryARB(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsQueryARB,glIsQueryARB(_p0))
    _result = glCalls().glIsQueryARB(_p0);
    POST_USER_CALL(glIsQueryARB,glIsQueryARB(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsRenderbuffer(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsRenderbuffer,glIsRenderbuffer(_p0))
    _result = glCalls().glIsRenderbuffer(_p0);
    POST_USER_CALL(glIsRenderbuffer,glIsRenderbuffer(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsRenderbufferEXT(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsRenderbufferEXT,glIsRenderbufferEXT(_p0))
    _result = glCalls().glIsRenderbufferEXT(_p0);
    POST_USER_CALL(glIsRenderbufferEXT,glIsRenderbufferEXT(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsShader(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsShader,glIsShader(_p0))
    _result = glCalls().glIsShader(_p0);
    POST_USER_CALL(glIsShader,glIsShader(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsTexture(GLuint texture)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsTexture,glIsTexture(texture))
    _result = glCalls().glIsTexture(texture);
    POST_USER_CALL(glIsTexture,glIsTexture(texture))
    return _result;
}

GLboolean GLAPIENTRY glIsTextureEXT(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsTextureEXT,glIsTextureEXT(_p0))
    _result = glCalls().glIsTextureEXT(_p0);
    POST_USER_CALL(glIsTextureEXT,glIsTextureEXT(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsTransformFeedbackNV(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsTransformFeedbackNV,glIsTransformFeedbackNV(_p0))
    _result = glCalls().glIsTransformFeedbackNV(_p0);
    POST_USER_CALL(glIsTransformFeedbackNV,glIsTransformFeedbackNV(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsVariantEnabledEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsVariantEnabledEXT,glIsVariantEnabledEXT(_p0,_p1))
    _result = glCalls().glIsVariantEnabledEXT(_p0,_p1);
    POST_USER_CALL(glIsVariantEnabledEXT,glIsVariantEnabledEXT(_p0,_p1))
    return _result;
}

GLboolean GLAPIENTRY glIsVertexArray(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsVertexArray,glIsVertexArray(_p0))
    _result = glCalls().glIsVertexArray(_p0);
    POST_USER_CALL(glIsVertexArray,glIsVertexArray(_p0))
    return _result;
}

GLboolean GLAPIENTRY glIsVertexArrayAPPLE(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glIsVertexArrayAPPLE,glIsVertexArrayAPPLE(_p0))
    _result = glCalls().glIsVertexArrayAPPLE(_p0);
    POST_USER_CALL(glIsVertexArrayAPPLE,glIsVertexArrayAPPLE(_p0))
    return _result;
}

void GLAPIENTRY glLightEnviSGIX(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glLightEnviSGIX,glLightEnviSGIX(_p0,_p1))
    glCalls().glLightEnviSGIX(_p0,_p1);
    POST_USER_CALL(glLightEnviSGIX,glLightEnviSGIX(_p0,_p1))
}

void GLAPIENTRY glLightModelf(GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glLightModelf,glLightModelf(pname,param))
    glCalls().glLightModelf(pname,param);
    POST_USER_CALL(glLightModelf,glLightModelf(pname,param))
}

void GLAPIENTRY glLightModelfv(GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glLightModelfv,glLightModelfv(pname,params))
    glCalls().glLightModelfv(pname,params);
    POST_USER_CALL(glLightModelfv,glLightModelfv(pname,params))
}

void GLAPIENTRY glLightModeli(GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glLightModeli,glLightModeli(pname,param))
    glCalls().glLightModeli(pname,param);
    POST_USER_CALL(glLightModeli,glLightModeli(pname,param))
}

void GLAPIENTRY glLightModeliv(GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glLightModeliv,glLightModeliv(pname,params))
    glCalls().glLightModeliv(pname,params);
    POST_USER_CALL(glLightModeliv,glLightModeliv(pname,params))
}

void GLAPIENTRY glLightf(GLenum light, GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glLightf,glLightf(light,pname,param))
    glCalls().glLightf(light,pname,param);
    POST_USER_CALL(glLightf,glLightf(light,pname,param))
}

void GLAPIENTRY glLightfv(GLenum light, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glLightfv,glLightfv(light,pname,params))
    glCalls().glLightfv(light,pname,params);
    POST_USER_CALL(glLightfv,glLightfv(light,pname,params))
}

void GLAPIENTRY glLighti(GLenum light, GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glLighti,glLighti(light,pname,param))
    glCalls().glLighti(light,pname,param);
    POST_USER_CALL(glLighti,glLighti(light,pname,param))
}

void GLAPIENTRY glLightiv(GLenum light, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glLightiv,glLightiv(light,pname,params))
    glCalls().glLightiv(light,pname,params);
    POST_USER_CALL(glLightiv,glLightiv(light,pname,params))
}

void GLAPIENTRY glLineStipple(GLint factor, GLushort pattern)
{
    gli().init();
    PREV_USER_CALL(glLineStipple,glLineStipple(factor,pattern))
    glCalls().glLineStipple(factor,pattern);
    POST_USER_CALL(glLineStipple,glLineStipple(factor,pattern))
}

void GLAPIENTRY glLineWidth(GLfloat width)
{
    gli().init();
    PREV_USER_CALL(glLineWidth,glLineWidth(width))
    glCalls().glLineWidth(width);
    POST_USER_CALL(glLineWidth,glLineWidth(width))
}

void GLAPIENTRY glLinkProgram(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glLinkProgram,glLinkProgram(_p0))
    glCalls().glLinkProgram(_p0);
    POST_USER_CALL(glLinkProgram,glLinkProgram(_p0))
}

void GLAPIENTRY glLinkProgramARB(GLhandleARB _p0)
{
    gli().init();
    PREV_USER_CALL(glLinkProgramARB,glLinkProgramARB(_p0))
    glCalls().glLinkProgramARB(_p0);
    POST_USER_CALL(glLinkProgramARB,glLinkProgramARB(_p0))
}

void GLAPIENTRY glListBase(GLuint base)
{
    gli().init();
    PREV_USER_CALL(glListBase,glListBase(base))
    glCalls().glListBase(base);
    POST_USER_CALL(glListBase,glListBase(base))
}

void GLAPIENTRY glListParameterfSGIX(GLuint _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glListParameterfSGIX,glListParameterfSGIX(_p0,_p1,_p2))
    glCalls().glListParameterfSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glListParameterfSGIX,glListParameterfSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glListParameterfvSGIX(GLuint _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glListParameterfvSGIX,glListParameterfvSGIX(_p0,_p1,_p2))
    glCalls().glListParameterfvSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glListParameterfvSGIX,glListParameterfvSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glListParameteriSGIX(GLuint _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glListParameteriSGIX,glListParameteriSGIX(_p0,_p1,_p2))
    glCalls().glListParameteriSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glListParameteriSGIX,glListParameteriSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glListParameterivSGIX(GLuint _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glListParameterivSGIX,glListParameterivSGIX(_p0,_p1,_p2))
    glCalls().glListParameterivSGIX(_p0,_p1,_p2);
    POST_USER_CALL(glListParameterivSGIX,glListParameterivSGIX(_p0,_p1,_p2))
}

void GLAPIENTRY glLoadIdentity()
{
    gli().init();
    PREV_USER_CALL(glLoadIdentity,glLoadIdentity())
    glCalls().glLoadIdentity();
    POST_USER_CALL(glLoadIdentity,glLoadIdentity())
}

void GLAPIENTRY glLoadIdentityDeformationMapSGIX(GLbitfield _p0)
{
    gli().init();
    PREV_USER_CALL(glLoadIdentityDeformationMapSGIX,glLoadIdentityDeformationMapSGIX(_p0))
    glCalls().glLoadIdentityDeformationMapSGIX(_p0);
    POST_USER_CALL(glLoadIdentityDeformationMapSGIX,glLoadIdentityDeformationMapSGIX(_p0))
}

void GLAPIENTRY glLoadMatrixd(const GLdouble *m)
{
    gli().init();
    PREV_USER_CALL(glLoadMatrixd,glLoadMatrixd(m))
    glCalls().glLoadMatrixd(m);
    POST_USER_CALL(glLoadMatrixd,glLoadMatrixd(m))
}

void GLAPIENTRY glLoadMatrixf(const GLfloat *m)
{
    gli().init();
    PREV_USER_CALL(glLoadMatrixf,glLoadMatrixf(m))
    glCalls().glLoadMatrixf(m);
    POST_USER_CALL(glLoadMatrixf,glLoadMatrixf(m))
}

void GLAPIENTRY glLoadName(GLuint name)
{
    gli().init();
    PREV_USER_CALL(glLoadName,glLoadName(name))
    glCalls().glLoadName(name);
    POST_USER_CALL(glLoadName,glLoadName(name))
}

void GLAPIENTRY glLoadProgramNV(GLenum _p0, GLuint _p1, GLsizei _p2, const GLubyte *_p3)
{
    gli().init();
    PREV_USER_CALL(glLoadProgramNV,glLoadProgramNV(_p0,_p1,_p2,_p3))
    glCalls().glLoadProgramNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glLoadProgramNV,glLoadProgramNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glLoadTransposeMatrixd(const GLdouble *m)
{
    gli().init();
    PREV_USER_CALL(glLoadTransposeMatrixd,glLoadTransposeMatrixd(m))
    glCalls().glLoadTransposeMatrixd(m);
    POST_USER_CALL(glLoadTransposeMatrixd,glLoadTransposeMatrixd(m))
}

void GLAPIENTRY glLoadTransposeMatrixdARB(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glLoadTransposeMatrixdARB,glLoadTransposeMatrixdARB(_p0))
    glCalls().glLoadTransposeMatrixdARB(_p0);
    POST_USER_CALL(glLoadTransposeMatrixdARB,glLoadTransposeMatrixdARB(_p0))
}

void GLAPIENTRY glLoadTransposeMatrixf(const GLfloat *m)
{
    gli().init();
    PREV_USER_CALL(glLoadTransposeMatrixf,glLoadTransposeMatrixf(m))
    glCalls().glLoadTransposeMatrixf(m);
    POST_USER_CALL(glLoadTransposeMatrixf,glLoadTransposeMatrixf(m))
}

void GLAPIENTRY glLoadTransposeMatrixfARB(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glLoadTransposeMatrixfARB,glLoadTransposeMatrixfARB(_p0))
    glCalls().glLoadTransposeMatrixfARB(_p0);
    POST_USER_CALL(glLoadTransposeMatrixfARB,glLoadTransposeMatrixfARB(_p0))
}

void GLAPIENTRY glLockArraysEXT(GLint _p0, GLsizei _p1)
{
    gli().init();
    PREV_USER_CALL(glLockArraysEXT,glLockArraysEXT(_p0,_p1))
    glCalls().glLockArraysEXT(_p0,_p1);
    POST_USER_CALL(glLockArraysEXT,glLockArraysEXT(_p0,_p1))
}

void GLAPIENTRY glLogicOp(GLenum opcode)
{
    gli().init();
    PREV_USER_CALL(glLogicOp,glLogicOp(opcode))
    glCalls().glLogicOp(opcode);
    POST_USER_CALL(glLogicOp,glLogicOp(opcode))
}

void GLAPIENTRY glMap1d(GLenum target, GLdouble u1, GLdouble u2, GLint stride, GLint order, const GLdouble *points)
{
    gli().init();
    PREV_USER_CALL(glMap1d,glMap1d(target,u1,u2,stride,order,points))
    glCalls().glMap1d(target,u1,u2,stride,order,points);
    POST_USER_CALL(glMap1d,glMap1d(target,u1,u2,stride,order,points))
}

void GLAPIENTRY glMap1f(GLenum target, GLfloat u1, GLfloat u2, GLint stride, GLint order, const GLfloat *points)
{
    gli().init();
    PREV_USER_CALL(glMap1f,glMap1f(target,u1,u2,stride,order,points))
    glCalls().glMap1f(target,u1,u2,stride,order,points);
    POST_USER_CALL(glMap1f,glMap1f(target,u1,u2,stride,order,points))
}

void GLAPIENTRY glMap2d(GLenum target, GLdouble u1, GLdouble u2, GLint ustride, GLint uorder, GLdouble v1, GLdouble v2, GLint vstride, GLint vorder, const GLdouble *points)
{
    gli().init();
    PREV_USER_CALL(glMap2d,glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points))
    glCalls().glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
    POST_USER_CALL(glMap2d,glMap2d(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points))
}

void GLAPIENTRY glMap2f(GLenum target, GLfloat u1, GLfloat u2, GLint ustride, GLint uorder, GLfloat v1, GLfloat v2, GLint vstride, GLint vorder, const GLfloat *points)
{
    gli().init();
    PREV_USER_CALL(glMap2f,glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points))
    glCalls().glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points);
    POST_USER_CALL(glMap2f,glMap2f(target,u1,u2,ustride,uorder,v1,v2,vstride,vorder,points))
}

GLvoid * GLAPIENTRY glMapBuffer(GLenum _p0, GLenum _p1)
{
    gli().init();
    GLvoid *_result;
    PREV_USER_CALL(glMapBuffer,glMapBuffer(_p0,_p1))
    _result = glCalls().glMapBuffer(_p0,_p1);
    POST_USER_CALL(glMapBuffer,glMapBuffer(_p0,_p1))
    return _result;
}

GLvoid * GLAPIENTRY glMapBufferARB(GLenum _p0, GLenum _p1)
{
    gli().init();
    GLvoid *_result;
    PREV_USER_CALL(glMapBufferARB,glMapBufferARB(_p0,_p1))
    _result = glCalls().glMapBufferARB(_p0,_p1);
    POST_USER_CALL(glMapBufferARB,glMapBufferARB(_p0,_p1))
    return _result;
}

GLvoid * GLAPIENTRY glMapBufferRange(GLenum _p0, GLintptr _p1, GLsizeiptr _p2, GLbitfield _p3)
{
    gli().init();
    GLvoid *_result;
    PREV_USER_CALL(glMapBufferRange,glMapBufferRange(_p0,_p1,_p2,_p3))
    _result = glCalls().glMapBufferRange(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMapBufferRange,glMapBufferRange(_p0,_p1,_p2,_p3))
    return _result;
}

void GLAPIENTRY glMapControlPointsNV(GLenum _p0, GLuint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLint _p5, GLint _p6, GLboolean _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glMapControlPointsNV,glMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glMapControlPointsNV,glMapControlPointsNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glMapGrid1d(GLint un, GLdouble u1, GLdouble u2)
{
    gli().init();
    PREV_USER_CALL(glMapGrid1d,glMapGrid1d(un,u1,u2))
    glCalls().glMapGrid1d(un,u1,u2);
    POST_USER_CALL(glMapGrid1d,glMapGrid1d(un,u1,u2))
}

void GLAPIENTRY glMapGrid1f(GLint un, GLfloat u1, GLfloat u2)
{
    gli().init();
    PREV_USER_CALL(glMapGrid1f,glMapGrid1f(un,u1,u2))
    glCalls().glMapGrid1f(un,u1,u2);
    POST_USER_CALL(glMapGrid1f,glMapGrid1f(un,u1,u2))
}

void GLAPIENTRY glMapGrid2d(GLint un, GLdouble u1, GLdouble u2, GLint vn, GLdouble v1, GLdouble v2)
{
    gli().init();
    PREV_USER_CALL(glMapGrid2d,glMapGrid2d(un,u1,u2,vn,v1,v2))
    glCalls().glMapGrid2d(un,u1,u2,vn,v1,v2);
    POST_USER_CALL(glMapGrid2d,glMapGrid2d(un,u1,u2,vn,v1,v2))
}

void GLAPIENTRY glMapGrid2f(GLint un, GLfloat u1, GLfloat u2, GLint vn, GLfloat v1, GLfloat v2)
{
    gli().init();
    PREV_USER_CALL(glMapGrid2f,glMapGrid2f(un,u1,u2,vn,v1,v2))
    glCalls().glMapGrid2f(un,u1,u2,vn,v1,v2);
    POST_USER_CALL(glMapGrid2f,glMapGrid2f(un,u1,u2,vn,v1,v2))
}

GLvoid * GLAPIENTRY glMapNamedBufferEXT(GLuint _p0, GLenum _p1)
{
    gli().init();
    GLvoid *_result;
    PREV_USER_CALL(glMapNamedBufferEXT,glMapNamedBufferEXT(_p0,_p1))
    _result = glCalls().glMapNamedBufferEXT(_p0,_p1);
    POST_USER_CALL(glMapNamedBufferEXT,glMapNamedBufferEXT(_p0,_p1))
    return _result;
}

GLvoid * GLAPIENTRY glMapObjectBufferATI(GLuint _p0)
{
    gli().init();
    GLvoid *_result;
    PREV_USER_CALL(glMapObjectBufferATI,glMapObjectBufferATI(_p0))
    _result = glCalls().glMapObjectBufferATI(_p0);
    POST_USER_CALL(glMapObjectBufferATI,glMapObjectBufferATI(_p0))
    return _result;
}

void GLAPIENTRY glMapParameterfvNV(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glMapParameterfvNV,glMapParameterfvNV(_p0,_p1,_p2))
    glCalls().glMapParameterfvNV(_p0,_p1,_p2);
    POST_USER_CALL(glMapParameterfvNV,glMapParameterfvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glMapParameterivNV(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glMapParameterivNV,glMapParameterivNV(_p0,_p1,_p2))
    glCalls().glMapParameterivNV(_p0,_p1,_p2);
    POST_USER_CALL(glMapParameterivNV,glMapParameterivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glMaterialf(GLenum face, GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glMaterialf,glMaterialf(face,pname,param))
    glCalls().glMaterialf(face,pname,param);
    POST_USER_CALL(glMaterialf,glMaterialf(face,pname,param))
}

void GLAPIENTRY glMaterialfv(GLenum face, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glMaterialfv,glMaterialfv(face,pname,params))
    glCalls().glMaterialfv(face,pname,params);
    POST_USER_CALL(glMaterialfv,glMaterialfv(face,pname,params))
}

void GLAPIENTRY glMateriali(GLenum face, GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glMateriali,glMateriali(face,pname,param))
    glCalls().glMateriali(face,pname,param);
    POST_USER_CALL(glMateriali,glMateriali(face,pname,param))
}

void GLAPIENTRY glMaterialiv(GLenum face, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glMaterialiv,glMaterialiv(face,pname,params))
    glCalls().glMaterialiv(face,pname,params);
    POST_USER_CALL(glMaterialiv,glMaterialiv(face,pname,params))
}

void GLAPIENTRY glMatrixFrustumEXT(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5, GLdouble _p6)
{
    gli().init();
    PREV_USER_CALL(glMatrixFrustumEXT,glMatrixFrustumEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glMatrixFrustumEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glMatrixFrustumEXT,glMatrixFrustumEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glMatrixIndexPointerARB(GLint _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glMatrixIndexPointerARB,glMatrixIndexPointerARB(_p0,_p1,_p2,_p3))
    glCalls().glMatrixIndexPointerARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMatrixIndexPointerARB,glMatrixIndexPointerARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMatrixIndexubvARB(GLint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixIndexubvARB,glMatrixIndexubvARB(_p0,_p1))
    glCalls().glMatrixIndexubvARB(_p0,_p1);
    POST_USER_CALL(glMatrixIndexubvARB,glMatrixIndexubvARB(_p0,_p1))
}

void GLAPIENTRY glMatrixIndexuivARB(GLint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixIndexuivARB,glMatrixIndexuivARB(_p0,_p1))
    glCalls().glMatrixIndexuivARB(_p0,_p1);
    POST_USER_CALL(glMatrixIndexuivARB,glMatrixIndexuivARB(_p0,_p1))
}

void GLAPIENTRY glMatrixIndexusvARB(GLint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixIndexusvARB,glMatrixIndexusvARB(_p0,_p1))
    glCalls().glMatrixIndexusvARB(_p0,_p1);
    POST_USER_CALL(glMatrixIndexusvARB,glMatrixIndexusvARB(_p0,_p1))
}

void GLAPIENTRY glMatrixLoadIdentityEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glMatrixLoadIdentityEXT,glMatrixLoadIdentityEXT(_p0))
    glCalls().glMatrixLoadIdentityEXT(_p0);
    POST_USER_CALL(glMatrixLoadIdentityEXT,glMatrixLoadIdentityEXT(_p0))
}

void GLAPIENTRY glMatrixLoadTransposedEXT(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixLoadTransposedEXT,glMatrixLoadTransposedEXT(_p0,_p1))
    glCalls().glMatrixLoadTransposedEXT(_p0,_p1);
    POST_USER_CALL(glMatrixLoadTransposedEXT,glMatrixLoadTransposedEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixLoadTransposefEXT(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixLoadTransposefEXT,glMatrixLoadTransposefEXT(_p0,_p1))
    glCalls().glMatrixLoadTransposefEXT(_p0,_p1);
    POST_USER_CALL(glMatrixLoadTransposefEXT,glMatrixLoadTransposefEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixLoaddEXT(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixLoaddEXT,glMatrixLoaddEXT(_p0,_p1))
    glCalls().glMatrixLoaddEXT(_p0,_p1);
    POST_USER_CALL(glMatrixLoaddEXT,glMatrixLoaddEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixLoadfEXT(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixLoadfEXT,glMatrixLoadfEXT(_p0,_p1))
    glCalls().glMatrixLoadfEXT(_p0,_p1);
    POST_USER_CALL(glMatrixLoadfEXT,glMatrixLoadfEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixMode(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glMatrixMode,glMatrixMode(mode))
    glCalls().glMatrixMode(mode);
    POST_USER_CALL(glMatrixMode,glMatrixMode(mode))
}

void GLAPIENTRY glMatrixMultTransposedEXT(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixMultTransposedEXT,glMatrixMultTransposedEXT(_p0,_p1))
    glCalls().glMatrixMultTransposedEXT(_p0,_p1);
    POST_USER_CALL(glMatrixMultTransposedEXT,glMatrixMultTransposedEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixMultTransposefEXT(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixMultTransposefEXT,glMatrixMultTransposefEXT(_p0,_p1))
    glCalls().glMatrixMultTransposefEXT(_p0,_p1);
    POST_USER_CALL(glMatrixMultTransposefEXT,glMatrixMultTransposefEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixMultdEXT(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixMultdEXT,glMatrixMultdEXT(_p0,_p1))
    glCalls().glMatrixMultdEXT(_p0,_p1);
    POST_USER_CALL(glMatrixMultdEXT,glMatrixMultdEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixMultfEXT(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glMatrixMultfEXT,glMatrixMultfEXT(_p0,_p1))
    glCalls().glMatrixMultfEXT(_p0,_p1);
    POST_USER_CALL(glMatrixMultfEXT,glMatrixMultfEXT(_p0,_p1))
}

void GLAPIENTRY glMatrixOrthoEXT(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5, GLdouble _p6)
{
    gli().init();
    PREV_USER_CALL(glMatrixOrthoEXT,glMatrixOrthoEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glMatrixOrthoEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glMatrixOrthoEXT,glMatrixOrthoEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glMatrixPopEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glMatrixPopEXT,glMatrixPopEXT(_p0))
    glCalls().glMatrixPopEXT(_p0);
    POST_USER_CALL(glMatrixPopEXT,glMatrixPopEXT(_p0))
}

void GLAPIENTRY glMatrixPushEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glMatrixPushEXT,glMatrixPushEXT(_p0))
    glCalls().glMatrixPushEXT(_p0);
    POST_USER_CALL(glMatrixPushEXT,glMatrixPushEXT(_p0))
}

void GLAPIENTRY glMatrixRotatedEXT(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4)
{
    gli().init();
    PREV_USER_CALL(glMatrixRotatedEXT,glMatrixRotatedEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMatrixRotatedEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glMatrixRotatedEXT,glMatrixRotatedEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glMatrixRotatefEXT(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glMatrixRotatefEXT,glMatrixRotatefEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMatrixRotatefEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glMatrixRotatefEXT,glMatrixRotatefEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glMatrixScaledEXT(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glMatrixScaledEXT,glMatrixScaledEXT(_p0,_p1,_p2,_p3))
    glCalls().glMatrixScaledEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMatrixScaledEXT,glMatrixScaledEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMatrixScalefEXT(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glMatrixScalefEXT,glMatrixScalefEXT(_p0,_p1,_p2,_p3))
    glCalls().glMatrixScalefEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMatrixScalefEXT,glMatrixScalefEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMatrixTranslatedEXT(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glMatrixTranslatedEXT,glMatrixTranslatedEXT(_p0,_p1,_p2,_p3))
    glCalls().glMatrixTranslatedEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMatrixTranslatedEXT,glMatrixTranslatedEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMatrixTranslatefEXT(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glMatrixTranslatefEXT,glMatrixTranslatefEXT(_p0,_p1,_p2,_p3))
    glCalls().glMatrixTranslatefEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMatrixTranslatefEXT,glMatrixTranslatefEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMinmax(GLenum target, GLenum internalformat, GLboolean sink)
{
    gli().init();
    PREV_USER_CALL(glMinmax,glMinmax(target,internalformat,sink))
    glCalls().glMinmax(target,internalformat,sink);
    POST_USER_CALL(glMinmax,glMinmax(target,internalformat,sink))
}

void GLAPIENTRY glMinmaxEXT(GLenum _p0, GLenum _p1, GLboolean _p2)
{
    gli().init();
    PREV_USER_CALL(glMinmaxEXT,glMinmaxEXT(_p0,_p1,_p2))
    glCalls().glMinmaxEXT(_p0,_p1,_p2);
    POST_USER_CALL(glMinmaxEXT,glMinmaxEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glMultMatrixd(const GLdouble *m)
{
    gli().init();
    PREV_USER_CALL(glMultMatrixd,glMultMatrixd(m))
    glCalls().glMultMatrixd(m);
    POST_USER_CALL(glMultMatrixd,glMultMatrixd(m))
}

void GLAPIENTRY glMultMatrixf(const GLfloat *m)
{
    gli().init();
    PREV_USER_CALL(glMultMatrixf,glMultMatrixf(m))
    glCalls().glMultMatrixf(m);
    POST_USER_CALL(glMultMatrixf,glMultMatrixf(m))
}

void GLAPIENTRY glMultTransposeMatrixd(const GLdouble *m)
{
    gli().init();
    PREV_USER_CALL(glMultTransposeMatrixd,glMultTransposeMatrixd(m))
    glCalls().glMultTransposeMatrixd(m);
    POST_USER_CALL(glMultTransposeMatrixd,glMultTransposeMatrixd(m))
}

void GLAPIENTRY glMultTransposeMatrixdARB(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glMultTransposeMatrixdARB,glMultTransposeMatrixdARB(_p0))
    glCalls().glMultTransposeMatrixdARB(_p0);
    POST_USER_CALL(glMultTransposeMatrixdARB,glMultTransposeMatrixdARB(_p0))
}

void GLAPIENTRY glMultTransposeMatrixf(const GLfloat *m)
{
    gli().init();
    PREV_USER_CALL(glMultTransposeMatrixf,glMultTransposeMatrixf(m))
    glCalls().glMultTransposeMatrixf(m);
    POST_USER_CALL(glMultTransposeMatrixf,glMultTransposeMatrixf(m))
}

void GLAPIENTRY glMultTransposeMatrixfARB(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glMultTransposeMatrixfARB,glMultTransposeMatrixfARB(_p0))
    glCalls().glMultTransposeMatrixfARB(_p0);
    POST_USER_CALL(glMultTransposeMatrixfARB,glMultTransposeMatrixfARB(_p0))
}

void GLAPIENTRY glMultiDrawArrays(GLenum _p0, GLint *_p1, GLsizei *_p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawArrays,glMultiDrawArrays(_p0,_p1,_p2,_p3))
    glCalls().glMultiDrawArrays(_p0,_p1,_p2,_p3);
    {
        for ( int i = 0; i < _p3; i++ )
            gli().incVertexCount(_p2[i]-_p1[i]);
    }
    POST_USER_CALL(glMultiDrawArrays,glMultiDrawArrays(_p0,_p1,_p2,_p3))
    gli().doEndBatchEvent();
}

void GLAPIENTRY glMultiDrawArraysEXT(GLenum _p0, GLint *_p1, GLsizei *_p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawArraysEXT,glMultiDrawArraysEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiDrawArraysEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiDrawArraysEXT,glMultiDrawArraysEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiDrawElementArrayAPPLE(GLenum _p0, const GLint *_p1, const GLsizei *_p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawElementArrayAPPLE,glMultiDrawElementArrayAPPLE(_p0,_p1,_p2,_p3))
    glCalls().glMultiDrawElementArrayAPPLE(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiDrawElementArrayAPPLE,glMultiDrawElementArrayAPPLE(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiDrawElements(GLenum _p0, const GLsizei *_p1, GLenum _p2, const GLvoid **_p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawElements,glMultiDrawElements(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMultiDrawElements(_p0,_p1,_p2,_p3,_p4);
    {
        for ( int i = 0; i < _p4; i++ )
            gli().incVertexCount(_p1[i]);
    }
    POST_USER_CALL(glMultiDrawElements,glMultiDrawElements(_p0,_p1,_p2,_p3,_p4))
    gli().doEndBatchEvent();
}

void GLAPIENTRY glMultiDrawElementsEXT(GLenum _p0, const GLsizei *_p1, GLenum _p2, const GLvoid **_p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawElementsEXT,glMultiDrawElementsEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMultiDrawElementsEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glMultiDrawElementsEXT,glMultiDrawElementsEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glMultiDrawRangeElementArrayAPPLE(GLenum _p0, GLuint _p1, GLuint _p2, const GLint *_p3, const GLsizei *_p4, GLsizei _p5)
{
    gli().init();
    PREV_USER_CALL(glMultiDrawRangeElementArrayAPPLE,glMultiDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glMultiDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glMultiDrawRangeElementArrayAPPLE,glMultiDrawRangeElementArrayAPPLE(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glMultiTexBufferEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexBufferEXT,glMultiTexBufferEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexBufferEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexBufferEXT,glMultiTexBufferEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexCoord1d(GLenum target, GLdouble s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1d,glMultiTexCoord1d(target,s))
    glCalls().glMultiTexCoord1d(target,s);
    POST_USER_CALL(glMultiTexCoord1d,glMultiTexCoord1d(target,s))
}

void GLAPIENTRY glMultiTexCoord1dARB(GLenum target, GLdouble s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1dARB,glMultiTexCoord1dARB(target,s))
    glCalls().glMultiTexCoord1dARB(target,s);
    POST_USER_CALL(glMultiTexCoord1dARB,glMultiTexCoord1dARB(target,s))
}

void GLAPIENTRY glMultiTexCoord1dv(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1dv,glMultiTexCoord1dv(target,v))
    glCalls().glMultiTexCoord1dv(target,v);
    POST_USER_CALL(glMultiTexCoord1dv,glMultiTexCoord1dv(target,v))
}

void GLAPIENTRY glMultiTexCoord1dvARB(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1dvARB,glMultiTexCoord1dvARB(target,v))
    glCalls().glMultiTexCoord1dvARB(target,v);
    POST_USER_CALL(glMultiTexCoord1dvARB,glMultiTexCoord1dvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord1f(GLenum target, GLfloat s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1f,glMultiTexCoord1f(target,s))
    glCalls().glMultiTexCoord1f(target,s);
    POST_USER_CALL(glMultiTexCoord1f,glMultiTexCoord1f(target,s))
}

void GLAPIENTRY glMultiTexCoord1fARB(GLenum target, GLfloat s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1fARB,glMultiTexCoord1fARB(target,s))
    glCalls().glMultiTexCoord1fARB(target,s);
    POST_USER_CALL(glMultiTexCoord1fARB,glMultiTexCoord1fARB(target,s))
}

void GLAPIENTRY glMultiTexCoord1fv(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1fv,glMultiTexCoord1fv(target,v))
    glCalls().glMultiTexCoord1fv(target,v);
    POST_USER_CALL(glMultiTexCoord1fv,glMultiTexCoord1fv(target,v))
}

void GLAPIENTRY glMultiTexCoord1fvARB(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1fvARB,glMultiTexCoord1fvARB(target,v))
    glCalls().glMultiTexCoord1fvARB(target,v);
    POST_USER_CALL(glMultiTexCoord1fvARB,glMultiTexCoord1fvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord1hNV(GLenum _p0, GLhalfNV _p1)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1hNV,glMultiTexCoord1hNV(_p0,_p1))
    glCalls().glMultiTexCoord1hNV(_p0,_p1);
    POST_USER_CALL(glMultiTexCoord1hNV,glMultiTexCoord1hNV(_p0,_p1))
}

void GLAPIENTRY glMultiTexCoord1hvNV(GLenum _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1hvNV,glMultiTexCoord1hvNV(_p0,_p1))
    glCalls().glMultiTexCoord1hvNV(_p0,_p1);
    POST_USER_CALL(glMultiTexCoord1hvNV,glMultiTexCoord1hvNV(_p0,_p1))
}

void GLAPIENTRY glMultiTexCoord1i(GLenum target, GLint s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1i,glMultiTexCoord1i(target,s))
    glCalls().glMultiTexCoord1i(target,s);
    POST_USER_CALL(glMultiTexCoord1i,glMultiTexCoord1i(target,s))
}

void GLAPIENTRY glMultiTexCoord1iARB(GLenum target, GLint s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1iARB,glMultiTexCoord1iARB(target,s))
    glCalls().glMultiTexCoord1iARB(target,s);
    POST_USER_CALL(glMultiTexCoord1iARB,glMultiTexCoord1iARB(target,s))
}

void GLAPIENTRY glMultiTexCoord1iv(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1iv,glMultiTexCoord1iv(target,v))
    glCalls().glMultiTexCoord1iv(target,v);
    POST_USER_CALL(glMultiTexCoord1iv,glMultiTexCoord1iv(target,v))
}

void GLAPIENTRY glMultiTexCoord1ivARB(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1ivARB,glMultiTexCoord1ivARB(target,v))
    glCalls().glMultiTexCoord1ivARB(target,v);
    POST_USER_CALL(glMultiTexCoord1ivARB,glMultiTexCoord1ivARB(target,v))
}

void GLAPIENTRY glMultiTexCoord1s(GLenum target, GLshort s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1s,glMultiTexCoord1s(target,s))
    glCalls().glMultiTexCoord1s(target,s);
    POST_USER_CALL(glMultiTexCoord1s,glMultiTexCoord1s(target,s))
}

void GLAPIENTRY glMultiTexCoord1sARB(GLenum target, GLshort s)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1sARB,glMultiTexCoord1sARB(target,s))
    glCalls().glMultiTexCoord1sARB(target,s);
    POST_USER_CALL(glMultiTexCoord1sARB,glMultiTexCoord1sARB(target,s))
}

void GLAPIENTRY glMultiTexCoord1sv(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1sv,glMultiTexCoord1sv(target,v))
    glCalls().glMultiTexCoord1sv(target,v);
    POST_USER_CALL(glMultiTexCoord1sv,glMultiTexCoord1sv(target,v))
}

void GLAPIENTRY glMultiTexCoord1svARB(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord1svARB,glMultiTexCoord1svARB(target,v))
    glCalls().glMultiTexCoord1svARB(target,v);
    POST_USER_CALL(glMultiTexCoord1svARB,glMultiTexCoord1svARB(target,v))
}

void GLAPIENTRY glMultiTexCoord2d(GLenum target, GLdouble s, GLdouble t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2d,glMultiTexCoord2d(target,s,t))
    glCalls().glMultiTexCoord2d(target,s,t);
    POST_USER_CALL(glMultiTexCoord2d,glMultiTexCoord2d(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2dARB(GLenum target, GLdouble s, GLdouble t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2dARB,glMultiTexCoord2dARB(target,s,t))
    glCalls().glMultiTexCoord2dARB(target,s,t);
    POST_USER_CALL(glMultiTexCoord2dARB,glMultiTexCoord2dARB(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2dv(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2dv,glMultiTexCoord2dv(target,v))
    glCalls().glMultiTexCoord2dv(target,v);
    POST_USER_CALL(glMultiTexCoord2dv,glMultiTexCoord2dv(target,v))
}

void GLAPIENTRY glMultiTexCoord2dvARB(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2dvARB,glMultiTexCoord2dvARB(target,v))
    glCalls().glMultiTexCoord2dvARB(target,v);
    POST_USER_CALL(glMultiTexCoord2dvARB,glMultiTexCoord2dvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord2f(GLenum target, GLfloat s, GLfloat t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2f,glMultiTexCoord2f(target,s,t))
    glCalls().glMultiTexCoord2f(target,s,t);
    POST_USER_CALL(glMultiTexCoord2f,glMultiTexCoord2f(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2fARB(GLenum target, GLfloat s, GLfloat t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2fARB,glMultiTexCoord2fARB(target,s,t))
    glCalls().glMultiTexCoord2fARB(target,s,t);
    POST_USER_CALL(glMultiTexCoord2fARB,glMultiTexCoord2fARB(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2fv(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2fv,glMultiTexCoord2fv(target,v))
    glCalls().glMultiTexCoord2fv(target,v);
    POST_USER_CALL(glMultiTexCoord2fv,glMultiTexCoord2fv(target,v))
}

void GLAPIENTRY glMultiTexCoord2fvARB(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2fvARB,glMultiTexCoord2fvARB(target,v))
    glCalls().glMultiTexCoord2fvARB(target,v);
    POST_USER_CALL(glMultiTexCoord2fvARB,glMultiTexCoord2fvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord2hNV(GLenum _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2hNV,glMultiTexCoord2hNV(_p0,_p1,_p2))
    glCalls().glMultiTexCoord2hNV(_p0,_p1,_p2);
    POST_USER_CALL(glMultiTexCoord2hNV,glMultiTexCoord2hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glMultiTexCoord2hvNV(GLenum _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2hvNV,glMultiTexCoord2hvNV(_p0,_p1))
    glCalls().glMultiTexCoord2hvNV(_p0,_p1);
    POST_USER_CALL(glMultiTexCoord2hvNV,glMultiTexCoord2hvNV(_p0,_p1))
}

void GLAPIENTRY glMultiTexCoord2i(GLenum target, GLint s, GLint t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2i,glMultiTexCoord2i(target,s,t))
    glCalls().glMultiTexCoord2i(target,s,t);
    POST_USER_CALL(glMultiTexCoord2i,glMultiTexCoord2i(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2iARB(GLenum target, GLint s, GLint t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2iARB,glMultiTexCoord2iARB(target,s,t))
    glCalls().glMultiTexCoord2iARB(target,s,t);
    POST_USER_CALL(glMultiTexCoord2iARB,glMultiTexCoord2iARB(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2iv(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2iv,glMultiTexCoord2iv(target,v))
    glCalls().glMultiTexCoord2iv(target,v);
    POST_USER_CALL(glMultiTexCoord2iv,glMultiTexCoord2iv(target,v))
}

void GLAPIENTRY glMultiTexCoord2ivARB(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2ivARB,glMultiTexCoord2ivARB(target,v))
    glCalls().glMultiTexCoord2ivARB(target,v);
    POST_USER_CALL(glMultiTexCoord2ivARB,glMultiTexCoord2ivARB(target,v))
}

void GLAPIENTRY glMultiTexCoord2s(GLenum target, GLshort s, GLshort t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2s,glMultiTexCoord2s(target,s,t))
    glCalls().glMultiTexCoord2s(target,s,t);
    POST_USER_CALL(glMultiTexCoord2s,glMultiTexCoord2s(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2sARB(GLenum target, GLshort s, GLshort t)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2sARB,glMultiTexCoord2sARB(target,s,t))
    glCalls().glMultiTexCoord2sARB(target,s,t);
    POST_USER_CALL(glMultiTexCoord2sARB,glMultiTexCoord2sARB(target,s,t))
}

void GLAPIENTRY glMultiTexCoord2sv(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2sv,glMultiTexCoord2sv(target,v))
    glCalls().glMultiTexCoord2sv(target,v);
    POST_USER_CALL(glMultiTexCoord2sv,glMultiTexCoord2sv(target,v))
}

void GLAPIENTRY glMultiTexCoord2svARB(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord2svARB,glMultiTexCoord2svARB(target,v))
    glCalls().glMultiTexCoord2svARB(target,v);
    POST_USER_CALL(glMultiTexCoord2svARB,glMultiTexCoord2svARB(target,v))
}

void GLAPIENTRY glMultiTexCoord3d(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3d,glMultiTexCoord3d(target,s,t,r))
    glCalls().glMultiTexCoord3d(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3d,glMultiTexCoord3d(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3dARB,glMultiTexCoord3dARB(target,s,t,r))
    glCalls().glMultiTexCoord3dARB(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3dARB,glMultiTexCoord3dARB(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3dv(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3dv,glMultiTexCoord3dv(target,v))
    glCalls().glMultiTexCoord3dv(target,v);
    POST_USER_CALL(glMultiTexCoord3dv,glMultiTexCoord3dv(target,v))
}

void GLAPIENTRY glMultiTexCoord3dvARB(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3dvARB,glMultiTexCoord3dvARB(target,v))
    glCalls().glMultiTexCoord3dvARB(target,v);
    POST_USER_CALL(glMultiTexCoord3dvARB,glMultiTexCoord3dvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord3f(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3f,glMultiTexCoord3f(target,s,t,r))
    glCalls().glMultiTexCoord3f(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3f,glMultiTexCoord3f(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3fARB,glMultiTexCoord3fARB(target,s,t,r))
    glCalls().glMultiTexCoord3fARB(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3fARB,glMultiTexCoord3fARB(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3fv(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3fv,glMultiTexCoord3fv(target,v))
    glCalls().glMultiTexCoord3fv(target,v);
    POST_USER_CALL(glMultiTexCoord3fv,glMultiTexCoord3fv(target,v))
}

void GLAPIENTRY glMultiTexCoord3fvARB(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3fvARB,glMultiTexCoord3fvARB(target,v))
    glCalls().glMultiTexCoord3fvARB(target,v);
    POST_USER_CALL(glMultiTexCoord3fvARB,glMultiTexCoord3fvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord3hNV(GLenum _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3hNV,glMultiTexCoord3hNV(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexCoord3hNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexCoord3hNV,glMultiTexCoord3hNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexCoord3hvNV(GLenum _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3hvNV,glMultiTexCoord3hvNV(_p0,_p1))
    glCalls().glMultiTexCoord3hvNV(_p0,_p1);
    POST_USER_CALL(glMultiTexCoord3hvNV,glMultiTexCoord3hvNV(_p0,_p1))
}

void GLAPIENTRY glMultiTexCoord3i(GLenum target, GLint s, GLint t, GLint r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3i,glMultiTexCoord3i(target,s,t,r))
    glCalls().glMultiTexCoord3i(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3i,glMultiTexCoord3i(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3iARB(GLenum target, GLint s, GLint t, GLint r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3iARB,glMultiTexCoord3iARB(target,s,t,r))
    glCalls().glMultiTexCoord3iARB(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3iARB,glMultiTexCoord3iARB(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3iv(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3iv,glMultiTexCoord3iv(target,v))
    glCalls().glMultiTexCoord3iv(target,v);
    POST_USER_CALL(glMultiTexCoord3iv,glMultiTexCoord3iv(target,v))
}

void GLAPIENTRY glMultiTexCoord3ivARB(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3ivARB,glMultiTexCoord3ivARB(target,v))
    glCalls().glMultiTexCoord3ivARB(target,v);
    POST_USER_CALL(glMultiTexCoord3ivARB,glMultiTexCoord3ivARB(target,v))
}

void GLAPIENTRY glMultiTexCoord3s(GLenum target, GLshort s, GLshort t, GLshort r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3s,glMultiTexCoord3s(target,s,t,r))
    glCalls().glMultiTexCoord3s(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3s,glMultiTexCoord3s(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3sARB(GLenum target, GLshort s, GLshort t, GLshort r)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3sARB,glMultiTexCoord3sARB(target,s,t,r))
    glCalls().glMultiTexCoord3sARB(target,s,t,r);
    POST_USER_CALL(glMultiTexCoord3sARB,glMultiTexCoord3sARB(target,s,t,r))
}

void GLAPIENTRY glMultiTexCoord3sv(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3sv,glMultiTexCoord3sv(target,v))
    glCalls().glMultiTexCoord3sv(target,v);
    POST_USER_CALL(glMultiTexCoord3sv,glMultiTexCoord3sv(target,v))
}

void GLAPIENTRY glMultiTexCoord3svARB(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord3svARB,glMultiTexCoord3svARB(target,v))
    glCalls().glMultiTexCoord3svARB(target,v);
    POST_USER_CALL(glMultiTexCoord3svARB,glMultiTexCoord3svARB(target,v))
}

void GLAPIENTRY glMultiTexCoord4d(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4d,glMultiTexCoord4d(target,s,t,r,q))
    glCalls().glMultiTexCoord4d(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4d,glMultiTexCoord4d(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4dARB(GLenum target, GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4dARB,glMultiTexCoord4dARB(target,s,t,r,q))
    glCalls().glMultiTexCoord4dARB(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4dARB,glMultiTexCoord4dARB(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4dv(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4dv,glMultiTexCoord4dv(target,v))
    glCalls().glMultiTexCoord4dv(target,v);
    POST_USER_CALL(glMultiTexCoord4dv,glMultiTexCoord4dv(target,v))
}

void GLAPIENTRY glMultiTexCoord4dvARB(GLenum target, const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4dvARB,glMultiTexCoord4dvARB(target,v))
    glCalls().glMultiTexCoord4dvARB(target,v);
    POST_USER_CALL(glMultiTexCoord4dvARB,glMultiTexCoord4dvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord4f(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4f,glMultiTexCoord4f(target,s,t,r,q))
    glCalls().glMultiTexCoord4f(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4f,glMultiTexCoord4f(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4fARB(GLenum target, GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4fARB,glMultiTexCoord4fARB(target,s,t,r,q))
    glCalls().glMultiTexCoord4fARB(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4fARB,glMultiTexCoord4fARB(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4fv(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4fv,glMultiTexCoord4fv(target,v))
    glCalls().glMultiTexCoord4fv(target,v);
    POST_USER_CALL(glMultiTexCoord4fv,glMultiTexCoord4fv(target,v))
}

void GLAPIENTRY glMultiTexCoord4fvARB(GLenum target, const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4fvARB,glMultiTexCoord4fvARB(target,v))
    glCalls().glMultiTexCoord4fvARB(target,v);
    POST_USER_CALL(glMultiTexCoord4fvARB,glMultiTexCoord4fvARB(target,v))
}

void GLAPIENTRY glMultiTexCoord4hNV(GLenum _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3, GLhalfNV _p4)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4hNV,glMultiTexCoord4hNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMultiTexCoord4hNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glMultiTexCoord4hNV,glMultiTexCoord4hNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glMultiTexCoord4hvNV(GLenum _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4hvNV,glMultiTexCoord4hvNV(_p0,_p1))
    glCalls().glMultiTexCoord4hvNV(_p0,_p1);
    POST_USER_CALL(glMultiTexCoord4hvNV,glMultiTexCoord4hvNV(_p0,_p1))
}

void GLAPIENTRY glMultiTexCoord4i(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4i,glMultiTexCoord4i(target,s,t,r,q))
    glCalls().glMultiTexCoord4i(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4i,glMultiTexCoord4i(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4iARB(GLenum target, GLint s, GLint t, GLint r, GLint q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4iARB,glMultiTexCoord4iARB(target,s,t,r,q))
    glCalls().glMultiTexCoord4iARB(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4iARB,glMultiTexCoord4iARB(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4iv(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4iv,glMultiTexCoord4iv(target,v))
    glCalls().glMultiTexCoord4iv(target,v);
    POST_USER_CALL(glMultiTexCoord4iv,glMultiTexCoord4iv(target,v))
}

void GLAPIENTRY glMultiTexCoord4ivARB(GLenum target, const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4ivARB,glMultiTexCoord4ivARB(target,v))
    glCalls().glMultiTexCoord4ivARB(target,v);
    POST_USER_CALL(glMultiTexCoord4ivARB,glMultiTexCoord4ivARB(target,v))
}

void GLAPIENTRY glMultiTexCoord4s(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4s,glMultiTexCoord4s(target,s,t,r,q))
    glCalls().glMultiTexCoord4s(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4s,glMultiTexCoord4s(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4sARB(GLenum target, GLshort s, GLshort t, GLshort r, GLshort q)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4sARB,glMultiTexCoord4sARB(target,s,t,r,q))
    glCalls().glMultiTexCoord4sARB(target,s,t,r,q);
    POST_USER_CALL(glMultiTexCoord4sARB,glMultiTexCoord4sARB(target,s,t,r,q))
}

void GLAPIENTRY glMultiTexCoord4sv(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4sv,glMultiTexCoord4sv(target,v))
    glCalls().glMultiTexCoord4sv(target,v);
    POST_USER_CALL(glMultiTexCoord4sv,glMultiTexCoord4sv(target,v))
}

void GLAPIENTRY glMultiTexCoord4svARB(GLenum target, const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoord4svARB,glMultiTexCoord4svARB(target,v))
    glCalls().glMultiTexCoord4svARB(target,v);
    POST_USER_CALL(glMultiTexCoord4svARB,glMultiTexCoord4svARB(target,v))
}

void GLAPIENTRY glMultiTexCoordPointerEXT(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glMultiTexCoordPointerEXT,glMultiTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glMultiTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glMultiTexCoordPointerEXT,glMultiTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glMultiTexEnvfEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexEnvfEXT,glMultiTexEnvfEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexEnvfEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexEnvfEXT,glMultiTexEnvfEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexEnvfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexEnvfvEXT,glMultiTexEnvfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexEnvfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexEnvfvEXT,glMultiTexEnvfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexEnviEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexEnviEXT,glMultiTexEnviEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexEnviEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexEnviEXT,glMultiTexEnviEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexEnvivEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexEnvivEXT,glMultiTexEnvivEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexEnvivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexEnvivEXT,glMultiTexEnvivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGendEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGendEXT,glMultiTexGendEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGendEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGendEXT,glMultiTexGendEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGendvEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGendvEXT,glMultiTexGendvEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGendvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGendvEXT,glMultiTexGendvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGenfEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGenfEXT,glMultiTexGenfEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGenfEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGenfEXT,glMultiTexGenfEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGenfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGenfvEXT,glMultiTexGenfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGenfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGenfvEXT,glMultiTexGenfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGeniEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGeniEXT,glMultiTexGeniEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGeniEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGeniEXT,glMultiTexGeniEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexGenivEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexGenivEXT,glMultiTexGenivEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexGenivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexGenivEXT,glMultiTexGenivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLint _p5, GLenum _p6, GLenum _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glMultiTexImage1DEXT,glMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glMultiTexImage1DEXT,glMultiTexImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glMultiTexImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLenum _p7, GLenum _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glMultiTexImage2DEXT,glMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glMultiTexImage2DEXT,glMultiTexImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glMultiTexImage3DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLsizei _p6, GLint _p7, GLenum _p8, GLenum _p9, const GLvoid *_p10)
{
    gli().init();
    PREV_USER_CALL(glMultiTexImage3DEXT,glMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glMultiTexImage3DEXT,glMultiTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glMultiTexParameterIivEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameterIivEXT,glMultiTexParameterIivEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameterIivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameterIivEXT,glMultiTexParameterIivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexParameterIuivEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameterIuivEXT,glMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameterIuivEXT,glMultiTexParameterIuivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexParameterfEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameterfEXT,glMultiTexParameterfEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameterfEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameterfEXT,glMultiTexParameterfEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexParameterfvEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameterfvEXT,glMultiTexParameterfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameterfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameterfvEXT,glMultiTexParameterfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexParameteriEXT(GLenum _p0, GLenum _p1, GLenum _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameteriEXT,glMultiTexParameteriEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameteriEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameteriEXT,glMultiTexParameteriEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexParameterivEXT(GLenum _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glMultiTexParameterivEXT,glMultiTexParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glMultiTexParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glMultiTexParameterivEXT,glMultiTexParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glMultiTexRenderbufferEXT(GLenum _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glMultiTexRenderbufferEXT,glMultiTexRenderbufferEXT(_p0,_p1,_p2))
    glCalls().glMultiTexRenderbufferEXT(_p0,_p1,_p2);
    POST_USER_CALL(glMultiTexRenderbufferEXT,glMultiTexRenderbufferEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glMultiTexSubImage1DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4, GLenum _p5, GLenum _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glMultiTexSubImage1DEXT,glMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glMultiTexSubImage1DEXT,glMultiTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glMultiTexSubImage2DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLenum _p7, GLenum _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glMultiTexSubImage2DEXT,glMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glMultiTexSubImage2DEXT,glMultiTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glMultiTexSubImage3DEXT(GLenum _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLsizei _p8, GLenum _p9, GLenum _p10, const GLvoid *_p11)
{
    gli().init();
    PREV_USER_CALL(glMultiTexSubImage3DEXT,glMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
    glCalls().glMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11);
    POST_USER_CALL(glMultiTexSubImage3DEXT,glMultiTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
}

void GLAPIENTRY glNamedBufferDataEXT(GLuint _p0, GLsizeiptr _p1, const GLvoid *_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glNamedBufferDataEXT,glNamedBufferDataEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedBufferDataEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedBufferDataEXT,glNamedBufferDataEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedBufferSubDataEXT(GLuint _p0, GLintptr _p1, GLsizeiptr _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glNamedBufferSubDataEXT,glNamedBufferSubDataEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedBufferSubDataEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedBufferSubDataEXT,glNamedBufferSubDataEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedFramebufferRenderbufferEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferRenderbufferEXT,glNamedFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedFramebufferRenderbufferEXT,glNamedFramebufferRenderbufferEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedFramebufferTexture1DEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTexture1DEXT,glNamedFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedFramebufferTexture1DEXT,glNamedFramebufferTexture1DEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedFramebufferTexture2DEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTexture2DEXT,glNamedFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedFramebufferTexture2DEXT,glNamedFramebufferTexture2DEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedFramebufferTexture3DEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTexture3DEXT,glNamedFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glNamedFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glNamedFramebufferTexture3DEXT,glNamedFramebufferTexture3DEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glNamedFramebufferTextureEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTextureEXT,glNamedFramebufferTextureEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedFramebufferTextureEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedFramebufferTextureEXT,glNamedFramebufferTextureEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedFramebufferTextureFaceEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLint _p3, GLenum _p4)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTextureFaceEXT,glNamedFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedFramebufferTextureFaceEXT,glNamedFramebufferTextureFaceEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedFramebufferTextureLayerEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glNamedFramebufferTextureLayerEXT,glNamedFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedFramebufferTextureLayerEXT,glNamedFramebufferTextureLayerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedProgramLocalParameter4dEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5, GLdouble _p6)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameter4dEXT,glNamedProgramLocalParameter4dEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glNamedProgramLocalParameter4dEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glNamedProgramLocalParameter4dEXT,glNamedProgramLocalParameter4dEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glNamedProgramLocalParameter4dvEXT(GLuint _p0, GLenum _p1, GLuint _p2, const GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameter4dvEXT,glNamedProgramLocalParameter4dvEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedProgramLocalParameter4dvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedProgramLocalParameter4dvEXT,glNamedProgramLocalParameter4dvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedProgramLocalParameter4fEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLfloat _p3, GLfloat _p4, GLfloat _p5, GLfloat _p6)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameter4fEXT,glNamedProgramLocalParameter4fEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glNamedProgramLocalParameter4fEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glNamedProgramLocalParameter4fEXT,glNamedProgramLocalParameter4fEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glNamedProgramLocalParameter4fvEXT(GLuint _p0, GLenum _p1, GLuint _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameter4fvEXT,glNamedProgramLocalParameter4fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedProgramLocalParameter4fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedProgramLocalParameter4fvEXT,glNamedProgramLocalParameter4fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedProgramLocalParameterI4iEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLint _p3, GLint _p4, GLint _p5, GLint _p6)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameterI4iEXT,glNamedProgramLocalParameterI4iEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glNamedProgramLocalParameterI4iEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glNamedProgramLocalParameterI4iEXT,glNamedProgramLocalParameterI4iEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glNamedProgramLocalParameterI4ivEXT(GLuint _p0, GLenum _p1, GLuint _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameterI4ivEXT,glNamedProgramLocalParameterI4ivEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedProgramLocalParameterI4ivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedProgramLocalParameterI4ivEXT,glNamedProgramLocalParameterI4ivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedProgramLocalParameterI4uiEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5, GLuint _p6)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameterI4uiEXT,glNamedProgramLocalParameterI4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glNamedProgramLocalParameterI4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glNamedProgramLocalParameterI4uiEXT,glNamedProgramLocalParameterI4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glNamedProgramLocalParameterI4uivEXT(GLuint _p0, GLenum _p1, GLuint _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameterI4uivEXT,glNamedProgramLocalParameterI4uivEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedProgramLocalParameterI4uivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedProgramLocalParameterI4uivEXT,glNamedProgramLocalParameterI4uivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedProgramLocalParameters4fvEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLsizei _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParameters4fvEXT,glNamedProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedProgramLocalParameters4fvEXT,glNamedProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedProgramLocalParametersI4ivEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLsizei _p3, const GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParametersI4ivEXT,glNamedProgramLocalParametersI4ivEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedProgramLocalParametersI4ivEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedProgramLocalParametersI4ivEXT,glNamedProgramLocalParametersI4ivEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedProgramLocalParametersI4uivEXT(GLuint _p0, GLenum _p1, GLuint _p2, GLsizei _p3, const GLuint *_p4)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramLocalParametersI4uivEXT,glNamedProgramLocalParametersI4uivEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedProgramLocalParametersI4uivEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedProgramLocalParametersI4uivEXT,glNamedProgramLocalParametersI4uivEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedProgramStringEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glNamedProgramStringEXT,glNamedProgramStringEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedProgramStringEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedProgramStringEXT,glNamedProgramStringEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNamedRenderbufferStorageEXT(GLuint _p0, GLenum _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glNamedRenderbufferStorageEXT,glNamedRenderbufferStorageEXT(_p0,_p1,_p2,_p3))
    glCalls().glNamedRenderbufferStorageEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNamedRenderbufferStorageEXT,glNamedRenderbufferStorageEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNamedRenderbufferStorageMultisampleCoverageEXT(GLuint _p0, GLsizei _p1, GLsizei _p2, GLenum _p3, GLsizei _p4, GLsizei _p5)
{
    gli().init();
    PREV_USER_CALL(glNamedRenderbufferStorageMultisampleCoverageEXT,glNamedRenderbufferStorageMultisampleCoverageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glNamedRenderbufferStorageMultisampleCoverageEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glNamedRenderbufferStorageMultisampleCoverageEXT,glNamedRenderbufferStorageMultisampleCoverageEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glNamedRenderbufferStorageMultisampleEXT(GLuint _p0, GLsizei _p1, GLenum _p2, GLsizei _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glNamedRenderbufferStorageMultisampleEXT,glNamedRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glNamedRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glNamedRenderbufferStorageMultisampleEXT,glNamedRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glNewList(GLuint list, GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glNewList,glNewList(list,mode))
    glCalls().glNewList(list,mode);
    POST_USER_CALL(glNewList,glNewList(list,mode))
}

GLuint GLAPIENTRY glNewObjectBufferATI(GLsizei _p0, const GLvoid *_p1, GLenum _p2)
{
    gli().init();
    GLuint _result;
    PREV_USER_CALL(glNewObjectBufferATI,glNewObjectBufferATI(_p0,_p1,_p2))
    _result = glCalls().glNewObjectBufferATI(_p0,_p1,_p2);
    POST_USER_CALL(glNewObjectBufferATI,glNewObjectBufferATI(_p0,_p1,_p2))
    return _result;
}

void GLAPIENTRY glNormal3b(GLbyte nx, GLbyte ny, GLbyte nz)
{
    gli().init();
    PREV_USER_CALL(glNormal3b,glNormal3b(nx,ny,nz))
    glCalls().glNormal3b(nx,ny,nz);
    POST_USER_CALL(glNormal3b,glNormal3b(nx,ny,nz))
}

void GLAPIENTRY glNormal3bv(const GLbyte *v)
{
    gli().init();
    PREV_USER_CALL(glNormal3bv,glNormal3bv(v))
    glCalls().glNormal3bv(v);
    POST_USER_CALL(glNormal3bv,glNormal3bv(v))
}

void GLAPIENTRY glNormal3d(GLdouble nx, GLdouble ny, GLdouble nz)
{
    gli().init();
    PREV_USER_CALL(glNormal3d,glNormal3d(nx,ny,nz))
    glCalls().glNormal3d(nx,ny,nz);
    POST_USER_CALL(glNormal3d,glNormal3d(nx,ny,nz))
}

void GLAPIENTRY glNormal3dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glNormal3dv,glNormal3dv(v))
    glCalls().glNormal3dv(v);
    POST_USER_CALL(glNormal3dv,glNormal3dv(v))
}

void GLAPIENTRY glNormal3f(GLfloat nx, GLfloat ny, GLfloat nz)
{
    gli().init();
    PREV_USER_CALL(glNormal3f,glNormal3f(nx,ny,nz))
    glCalls().glNormal3f(nx,ny,nz);
    POST_USER_CALL(glNormal3f,glNormal3f(nx,ny,nz))
}

void GLAPIENTRY glNormal3fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glNormal3fv,glNormal3fv(v))
    glCalls().glNormal3fv(v);
    POST_USER_CALL(glNormal3fv,glNormal3fv(v))
}

void GLAPIENTRY glNormal3hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glNormal3hNV,glNormal3hNV(_p0,_p1,_p2))
    glCalls().glNormal3hNV(_p0,_p1,_p2);
    POST_USER_CALL(glNormal3hNV,glNormal3hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glNormal3hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glNormal3hvNV,glNormal3hvNV(_p0))
    glCalls().glNormal3hvNV(_p0);
    POST_USER_CALL(glNormal3hvNV,glNormal3hvNV(_p0))
}

void GLAPIENTRY glNormal3i(GLint nx, GLint ny, GLint nz)
{
    gli().init();
    PREV_USER_CALL(glNormal3i,glNormal3i(nx,ny,nz))
    glCalls().glNormal3i(nx,ny,nz);
    POST_USER_CALL(glNormal3i,glNormal3i(nx,ny,nz))
}

void GLAPIENTRY glNormal3iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glNormal3iv,glNormal3iv(v))
    glCalls().glNormal3iv(v);
    POST_USER_CALL(glNormal3iv,glNormal3iv(v))
}

void GLAPIENTRY glNormal3s(GLshort nx, GLshort ny, GLshort nz)
{
    gli().init();
    PREV_USER_CALL(glNormal3s,glNormal3s(nx,ny,nz))
    glCalls().glNormal3s(nx,ny,nz);
    POST_USER_CALL(glNormal3s,glNormal3s(nx,ny,nz))
}

void GLAPIENTRY glNormal3sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glNormal3sv,glNormal3sv(v))
    glCalls().glNormal3sv(v);
    POST_USER_CALL(glNormal3sv,glNormal3sv(v))
}

void GLAPIENTRY glNormalPointer(GLenum type, GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glNormalPointer,glNormalPointer(type,stride,ptr))
    glCalls().glNormalPointer(type,stride,ptr);
    POST_USER_CALL(glNormalPointer,glNormalPointer(type,stride,ptr))
}

void GLAPIENTRY glNormalPointerEXT(GLenum _p0, GLsizei _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glNormalPointerEXT,glNormalPointerEXT(_p0,_p1,_p2,_p3))
    glCalls().glNormalPointerEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalPointerEXT,glNormalPointerEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalPointervINTEL(GLenum _p0, const GLvoid **_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalPointervINTEL,glNormalPointervINTEL(_p0,_p1))
    glCalls().glNormalPointervINTEL(_p0,_p1);
    POST_USER_CALL(glNormalPointervINTEL,glNormalPointervINTEL(_p0,_p1))
}

void GLAPIENTRY glNormalStream3bATI(GLenum _p0, GLbyte _p1, GLbyte _p2, GLbyte _p3)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3bATI,glNormalStream3bATI(_p0,_p1,_p2,_p3))
    glCalls().glNormalStream3bATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalStream3bATI,glNormalStream3bATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalStream3bvATI(GLenum _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3bvATI,glNormalStream3bvATI(_p0,_p1))
    glCalls().glNormalStream3bvATI(_p0,_p1);
    POST_USER_CALL(glNormalStream3bvATI,glNormalStream3bvATI(_p0,_p1))
}

void GLAPIENTRY glNormalStream3dATI(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3dATI,glNormalStream3dATI(_p0,_p1,_p2,_p3))
    glCalls().glNormalStream3dATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalStream3dATI,glNormalStream3dATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalStream3dvATI(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3dvATI,glNormalStream3dvATI(_p0,_p1))
    glCalls().glNormalStream3dvATI(_p0,_p1);
    POST_USER_CALL(glNormalStream3dvATI,glNormalStream3dvATI(_p0,_p1))
}

void GLAPIENTRY glNormalStream3fATI(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3fATI,glNormalStream3fATI(_p0,_p1,_p2,_p3))
    glCalls().glNormalStream3fATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalStream3fATI,glNormalStream3fATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalStream3fvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3fvATI,glNormalStream3fvATI(_p0,_p1))
    glCalls().glNormalStream3fvATI(_p0,_p1);
    POST_USER_CALL(glNormalStream3fvATI,glNormalStream3fvATI(_p0,_p1))
}

void GLAPIENTRY glNormalStream3iATI(GLenum _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3iATI,glNormalStream3iATI(_p0,_p1,_p2,_p3))
    glCalls().glNormalStream3iATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalStream3iATI,glNormalStream3iATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalStream3ivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3ivATI,glNormalStream3ivATI(_p0,_p1))
    glCalls().glNormalStream3ivATI(_p0,_p1);
    POST_USER_CALL(glNormalStream3ivATI,glNormalStream3ivATI(_p0,_p1))
}

void GLAPIENTRY glNormalStream3sATI(GLenum _p0, GLshort _p1, GLshort _p2, GLshort _p3)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3sATI,glNormalStream3sATI(_p0,_p1,_p2,_p3))
    glCalls().glNormalStream3sATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glNormalStream3sATI,glNormalStream3sATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glNormalStream3svATI(GLenum _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glNormalStream3svATI,glNormalStream3svATI(_p0,_p1))
    glCalls().glNormalStream3svATI(_p0,_p1);
    POST_USER_CALL(glNormalStream3svATI,glNormalStream3svATI(_p0,_p1))
}

void GLAPIENTRY glOrtho(GLdouble left, GLdouble right, GLdouble bottom, GLdouble top, GLdouble near_val, GLdouble far_val)
{
    gli().init();
    PREV_USER_CALL(glOrtho,glOrtho(left,right,bottom,top,near_val,far_val))
    glCalls().glOrtho(left,right,bottom,top,near_val,far_val);
    POST_USER_CALL(glOrtho,glOrtho(left,right,bottom,top,near_val,far_val))
}

void GLAPIENTRY glPNTrianglesfATI(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPNTrianglesfATI,glPNTrianglesfATI(_p0,_p1))
    glCalls().glPNTrianglesfATI(_p0,_p1);
    POST_USER_CALL(glPNTrianglesfATI,glPNTrianglesfATI(_p0,_p1))
}

void GLAPIENTRY glPNTrianglesiATI(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glPNTrianglesiATI,glPNTrianglesiATI(_p0,_p1))
    glCalls().glPNTrianglesiATI(_p0,_p1);
    POST_USER_CALL(glPNTrianglesiATI,glPNTrianglesiATI(_p0,_p1))
}

void GLAPIENTRY glPassTexCoordATI(GLuint _p0, GLuint _p1, GLenum _p2)
{
    gli().init();
    PREV_USER_CALL(glPassTexCoordATI,glPassTexCoordATI(_p0,_p1,_p2))
    glCalls().glPassTexCoordATI(_p0,_p1,_p2);
    POST_USER_CALL(glPassTexCoordATI,glPassTexCoordATI(_p0,_p1,_p2))
}

void GLAPIENTRY glPassThrough(GLfloat token)
{
    gli().init();
    PREV_USER_CALL(glPassThrough,glPassThrough(token))
    glCalls().glPassThrough(token);
    POST_USER_CALL(glPassThrough,glPassThrough(token))
}

void GLAPIENTRY glPauseTransformFeedbackNV()
{
    gli().init();
    PREV_USER_CALL(glPauseTransformFeedbackNV,glPauseTransformFeedbackNV())
    glCalls().glPauseTransformFeedbackNV();
    POST_USER_CALL(glPauseTransformFeedbackNV,glPauseTransformFeedbackNV())
}

void GLAPIENTRY glPixelDataRangeNV(GLenum _p0, GLsizei _p1, GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glPixelDataRangeNV,glPixelDataRangeNV(_p0,_p1,_p2))
    glCalls().glPixelDataRangeNV(_p0,_p1,_p2);
    POST_USER_CALL(glPixelDataRangeNV,glPixelDataRangeNV(_p0,_p1,_p2))
}

void GLAPIENTRY glPixelMapfv(GLenum map, GLsizei mapsize, const GLfloat *values)
{
    gli().init();
    PREV_USER_CALL(glPixelMapfv,glPixelMapfv(map,mapsize,values))
    glCalls().glPixelMapfv(map,mapsize,values);
    POST_USER_CALL(glPixelMapfv,glPixelMapfv(map,mapsize,values))
}

void GLAPIENTRY glPixelMapuiv(GLenum map, GLsizei mapsize, const GLuint *values)
{
    gli().init();
    PREV_USER_CALL(glPixelMapuiv,glPixelMapuiv(map,mapsize,values))
    glCalls().glPixelMapuiv(map,mapsize,values);
    POST_USER_CALL(glPixelMapuiv,glPixelMapuiv(map,mapsize,values))
}

void GLAPIENTRY glPixelMapusv(GLenum map, GLsizei mapsize, const GLushort *values)
{
    gli().init();
    PREV_USER_CALL(glPixelMapusv,glPixelMapusv(map,mapsize,values))
    glCalls().glPixelMapusv(map,mapsize,values);
    POST_USER_CALL(glPixelMapusv,glPixelMapusv(map,mapsize,values))
}

void GLAPIENTRY glPixelStoref(GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glPixelStoref,glPixelStoref(pname,param))
    glCalls().glPixelStoref(pname,param);
    POST_USER_CALL(glPixelStoref,glPixelStoref(pname,param))
}

void GLAPIENTRY glPixelStorei(GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glPixelStorei,glPixelStorei(pname,param))
    glCalls().glPixelStorei(pname,param);
    POST_USER_CALL(glPixelStorei,glPixelStorei(pname,param))
}

void GLAPIENTRY glPixelTexGenParameterfSGIS(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPixelTexGenParameterfSGIS,glPixelTexGenParameterfSGIS(_p0,_p1))
    glCalls().glPixelTexGenParameterfSGIS(_p0,_p1);
    POST_USER_CALL(glPixelTexGenParameterfSGIS,glPixelTexGenParameterfSGIS(_p0,_p1))
}

void GLAPIENTRY glPixelTexGenParameterfvSGIS(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glPixelTexGenParameterfvSGIS,glPixelTexGenParameterfvSGIS(_p0,_p1))
    glCalls().glPixelTexGenParameterfvSGIS(_p0,_p1);
    POST_USER_CALL(glPixelTexGenParameterfvSGIS,glPixelTexGenParameterfvSGIS(_p0,_p1))
}

void GLAPIENTRY glPixelTexGenParameteriSGIS(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glPixelTexGenParameteriSGIS,glPixelTexGenParameteriSGIS(_p0,_p1))
    glCalls().glPixelTexGenParameteriSGIS(_p0,_p1);
    POST_USER_CALL(glPixelTexGenParameteriSGIS,glPixelTexGenParameteriSGIS(_p0,_p1))
}

void GLAPIENTRY glPixelTexGenParameterivSGIS(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glPixelTexGenParameterivSGIS,glPixelTexGenParameterivSGIS(_p0,_p1))
    glCalls().glPixelTexGenParameterivSGIS(_p0,_p1);
    POST_USER_CALL(glPixelTexGenParameterivSGIS,glPixelTexGenParameterivSGIS(_p0,_p1))
}

void GLAPIENTRY glPixelTexGenSGIX(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glPixelTexGenSGIX,glPixelTexGenSGIX(_p0))
    glCalls().glPixelTexGenSGIX(_p0);
    POST_USER_CALL(glPixelTexGenSGIX,glPixelTexGenSGIX(_p0))
}

void GLAPIENTRY glPixelTransferf(GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glPixelTransferf,glPixelTransferf(pname,param))
    glCalls().glPixelTransferf(pname,param);
    POST_USER_CALL(glPixelTransferf,glPixelTransferf(pname,param))
}

void GLAPIENTRY glPixelTransferi(GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glPixelTransferi,glPixelTransferi(pname,param))
    glCalls().glPixelTransferi(pname,param);
    POST_USER_CALL(glPixelTransferi,glPixelTransferi(pname,param))
}

void GLAPIENTRY glPixelTransformParameterfEXT(GLenum _p0, GLenum _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glPixelTransformParameterfEXT,glPixelTransformParameterfEXT(_p0,_p1,_p2))
    glCalls().glPixelTransformParameterfEXT(_p0,_p1,_p2);
    POST_USER_CALL(glPixelTransformParameterfEXT,glPixelTransformParameterfEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glPixelTransformParameterfvEXT(GLenum _p0, GLenum _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glPixelTransformParameterfvEXT,glPixelTransformParameterfvEXT(_p0,_p1,_p2))
    glCalls().glPixelTransformParameterfvEXT(_p0,_p1,_p2);
    POST_USER_CALL(glPixelTransformParameterfvEXT,glPixelTransformParameterfvEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glPixelTransformParameteriEXT(GLenum _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glPixelTransformParameteriEXT,glPixelTransformParameteriEXT(_p0,_p1,_p2))
    glCalls().glPixelTransformParameteriEXT(_p0,_p1,_p2);
    POST_USER_CALL(glPixelTransformParameteriEXT,glPixelTransformParameteriEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glPixelTransformParameterivEXT(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glPixelTransformParameterivEXT,glPixelTransformParameterivEXT(_p0,_p1,_p2))
    glCalls().glPixelTransformParameterivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glPixelTransformParameterivEXT,glPixelTransformParameterivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glPixelZoom(GLfloat xfactor, GLfloat yfactor)
{
    gli().init();
    PREV_USER_CALL(glPixelZoom,glPixelZoom(xfactor,yfactor))
    glCalls().glPixelZoom(xfactor,yfactor);
    POST_USER_CALL(glPixelZoom,glPixelZoom(xfactor,yfactor))
}

void GLAPIENTRY glPointParameterf(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterf,glPointParameterf(_p0,_p1))
    glCalls().glPointParameterf(_p0,_p1);
    POST_USER_CALL(glPointParameterf,glPointParameterf(_p0,_p1))
}

void GLAPIENTRY glPointParameterfARB(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfARB,glPointParameterfARB(_p0,_p1))
    glCalls().glPointParameterfARB(_p0,_p1);
    POST_USER_CALL(glPointParameterfARB,glPointParameterfARB(_p0,_p1))
}

void GLAPIENTRY glPointParameterfEXT(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfEXT,glPointParameterfEXT(_p0,_p1))
    glCalls().glPointParameterfEXT(_p0,_p1);
    POST_USER_CALL(glPointParameterfEXT,glPointParameterfEXT(_p0,_p1))
}

void GLAPIENTRY glPointParameterfSGIS(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfSGIS,glPointParameterfSGIS(_p0,_p1))
    glCalls().glPointParameterfSGIS(_p0,_p1);
    POST_USER_CALL(glPointParameterfSGIS,glPointParameterfSGIS(_p0,_p1))
}

void GLAPIENTRY glPointParameterfv(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfv,glPointParameterfv(_p0,_p1))
    glCalls().glPointParameterfv(_p0,_p1);
    POST_USER_CALL(glPointParameterfv,glPointParameterfv(_p0,_p1))
}

void GLAPIENTRY glPointParameterfvARB(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfvARB,glPointParameterfvARB(_p0,_p1))
    glCalls().glPointParameterfvARB(_p0,_p1);
    POST_USER_CALL(glPointParameterfvARB,glPointParameterfvARB(_p0,_p1))
}

void GLAPIENTRY glPointParameterfvEXT(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfvEXT,glPointParameterfvEXT(_p0,_p1))
    glCalls().glPointParameterfvEXT(_p0,_p1);
    POST_USER_CALL(glPointParameterfvEXT,glPointParameterfvEXT(_p0,_p1))
}

void GLAPIENTRY glPointParameterfvSGIS(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterfvSGIS,glPointParameterfvSGIS(_p0,_p1))
    glCalls().glPointParameterfvSGIS(_p0,_p1);
    POST_USER_CALL(glPointParameterfvSGIS,glPointParameterfvSGIS(_p0,_p1))
}

void GLAPIENTRY glPointParameteri(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameteri,glPointParameteri(_p0,_p1))
    glCalls().glPointParameteri(_p0,_p1);
    POST_USER_CALL(glPointParameteri,glPointParameteri(_p0,_p1))
}

void GLAPIENTRY glPointParameteriNV(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameteriNV,glPointParameteriNV(_p0,_p1))
    glCalls().glPointParameteriNV(_p0,_p1);
    POST_USER_CALL(glPointParameteriNV,glPointParameteriNV(_p0,_p1))
}

void GLAPIENTRY glPointParameteriv(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameteriv,glPointParameteriv(_p0,_p1))
    glCalls().glPointParameteriv(_p0,_p1);
    POST_USER_CALL(glPointParameteriv,glPointParameteriv(_p0,_p1))
}

void GLAPIENTRY glPointParameterivNV(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glPointParameterivNV,glPointParameterivNV(_p0,_p1))
    glCalls().glPointParameterivNV(_p0,_p1);
    POST_USER_CALL(glPointParameterivNV,glPointParameterivNV(_p0,_p1))
}

void GLAPIENTRY glPointSize(GLfloat size)
{
    gli().init();
    PREV_USER_CALL(glPointSize,glPointSize(size))
    glCalls().glPointSize(size);
    POST_USER_CALL(glPointSize,glPointSize(size))
}

GLint GLAPIENTRY glPollAsyncSGIX(GLuint *_p0)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glPollAsyncSGIX,glPollAsyncSGIX(_p0))
    _result = glCalls().glPollAsyncSGIX(_p0);
    POST_USER_CALL(glPollAsyncSGIX,glPollAsyncSGIX(_p0))
    return _result;
}

GLint GLAPIENTRY glPollInstrumentsSGIX(GLint *_p0)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glPollInstrumentsSGIX,glPollInstrumentsSGIX(_p0))
    _result = glCalls().glPollInstrumentsSGIX(_p0);
    POST_USER_CALL(glPollInstrumentsSGIX,glPollInstrumentsSGIX(_p0))
    return _result;
}

void GLAPIENTRY glPolygonMode(GLenum face, GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glPolygonMode,glPolygonMode(face,mode))
    glCalls().glPolygonMode(face,mode);
    POST_USER_CALL(glPolygonMode,glPolygonMode(face,mode))
}

void GLAPIENTRY glPolygonOffset(GLfloat factor, GLfloat units)
{
    gli().init();
    PREV_USER_CALL(glPolygonOffset,glPolygonOffset(factor,units))
    glCalls().glPolygonOffset(factor,units);
    POST_USER_CALL(glPolygonOffset,glPolygonOffset(factor,units))
}

void GLAPIENTRY glPolygonOffsetEXT(GLfloat _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glPolygonOffsetEXT,glPolygonOffsetEXT(_p0,_p1))
    glCalls().glPolygonOffsetEXT(_p0,_p1);
    POST_USER_CALL(glPolygonOffsetEXT,glPolygonOffsetEXT(_p0,_p1))
}

void GLAPIENTRY glPolygonStipple(const GLubyte *mask)
{
    gli().init();
    PREV_USER_CALL(glPolygonStipple,glPolygonStipple(mask))
    glCalls().glPolygonStipple(mask);
    POST_USER_CALL(glPolygonStipple,glPolygonStipple(mask))
}

void GLAPIENTRY glPopAttrib()
{
    gli().init();
    PREV_USER_CALL(glPopAttrib,glPopAttrib())
    glCalls().glPopAttrib();
    POST_USER_CALL(glPopAttrib,glPopAttrib())
}

void GLAPIENTRY glPopClientAttrib()
{
    gli().init();
    PREV_USER_CALL(glPopClientAttrib,glPopClientAttrib())
    glCalls().glPopClientAttrib();
    POST_USER_CALL(glPopClientAttrib,glPopClientAttrib())
}

void GLAPIENTRY glPopMatrix()
{
    gli().init();
    PREV_USER_CALL(glPopMatrix,glPopMatrix())
    glCalls().glPopMatrix();
    POST_USER_CALL(glPopMatrix,glPopMatrix())
}

void GLAPIENTRY glPopName()
{
    gli().init();
    PREV_USER_CALL(glPopName,glPopName())
    glCalls().glPopName();
    POST_USER_CALL(glPopName,glPopName())
}

void GLAPIENTRY glPresentFrameDualFillNV(GLuint _p0, GLuint64EXT _p1, GLuint _p2, GLuint _p3, GLenum _p4, GLenum _p5, GLuint _p6, GLenum _p7, GLuint _p8, GLenum _p9, GLuint _p10, GLenum _p11, GLuint _p12)
{
    gli().init();
    PREV_USER_CALL(glPresentFrameDualFillNV,glPresentFrameDualFillNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
    glCalls().glPresentFrameDualFillNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12);
    POST_USER_CALL(glPresentFrameDualFillNV,glPresentFrameDualFillNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
}

void GLAPIENTRY glPresentFrameKeyedNV(GLuint _p0, GLuint64EXT _p1, GLuint _p2, GLuint _p3, GLenum _p4, GLenum _p5, GLuint _p6, GLuint _p7, GLenum _p8, GLuint _p9, GLuint _p10)
{
    gli().init();
    PREV_USER_CALL(glPresentFrameKeyedNV,glPresentFrameKeyedNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glPresentFrameKeyedNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glPresentFrameKeyedNV,glPresentFrameKeyedNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glPrimitiveRestartIndex(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glPrimitiveRestartIndex,glPrimitiveRestartIndex(_p0))
    glCalls().glPrimitiveRestartIndex(_p0);
    POST_USER_CALL(glPrimitiveRestartIndex,glPrimitiveRestartIndex(_p0))
}

void GLAPIENTRY glPrimitiveRestartIndexNV(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glPrimitiveRestartIndexNV,glPrimitiveRestartIndexNV(_p0))
    glCalls().glPrimitiveRestartIndexNV(_p0);
    POST_USER_CALL(glPrimitiveRestartIndexNV,glPrimitiveRestartIndexNV(_p0))
}

void GLAPIENTRY glPrimitiveRestartNV()
{
    gli().init();
    PREV_USER_CALL(glPrimitiveRestartNV,glPrimitiveRestartNV())
    glCalls().glPrimitiveRestartNV();
    POST_USER_CALL(glPrimitiveRestartNV,glPrimitiveRestartNV())
}

void GLAPIENTRY glPrioritizeTextures(GLsizei n, const GLuint *textures, const GLclampf *priorities)
{
    gli().init();
    PREV_USER_CALL(glPrioritizeTextures,glPrioritizeTextures(n,textures,priorities))
    glCalls().glPrioritizeTextures(n,textures,priorities);
    POST_USER_CALL(glPrioritizeTextures,glPrioritizeTextures(n,textures,priorities))
}

void GLAPIENTRY glPrioritizeTexturesEXT(GLsizei _p0, const GLuint *_p1, const GLclampf *_p2)
{
    gli().init();
    PREV_USER_CALL(glPrioritizeTexturesEXT,glPrioritizeTexturesEXT(_p0,_p1,_p2))
    glCalls().glPrioritizeTexturesEXT(_p0,_p1,_p2);
    POST_USER_CALL(glPrioritizeTexturesEXT,glPrioritizeTexturesEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramBufferParametersIivNV(GLenum _p0, GLuint _p1, GLuint _p2, GLsizei _p3, const GLint *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramBufferParametersIivNV,glProgramBufferParametersIivNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramBufferParametersIivNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramBufferParametersIivNV,glProgramBufferParametersIivNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramBufferParametersIuivNV(GLenum _p0, GLuint _p1, GLuint _p2, GLsizei _p3, const GLuint *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramBufferParametersIuivNV,glProgramBufferParametersIuivNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramBufferParametersIuivNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramBufferParametersIuivNV,glProgramBufferParametersIuivNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramBufferParametersfvNV(GLenum _p0, GLuint _p1, GLuint _p2, GLsizei _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramBufferParametersfvNV,glProgramBufferParametersfvNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramBufferParametersfvNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramBufferParametersfvNV,glProgramBufferParametersfvNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramEnvParameter4dARB(GLenum _p0, GLuint _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameter4dARB,glProgramEnvParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramEnvParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramEnvParameter4dARB,glProgramEnvParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramEnvParameter4dvARB(GLenum _p0, GLuint _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameter4dvARB,glProgramEnvParameter4dvARB(_p0,_p1,_p2))
    glCalls().glProgramEnvParameter4dvARB(_p0,_p1,_p2);
    POST_USER_CALL(glProgramEnvParameter4dvARB,glProgramEnvParameter4dvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramEnvParameter4fARB(GLenum _p0, GLuint _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4, GLfloat _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameter4fARB,glProgramEnvParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramEnvParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramEnvParameter4fARB,glProgramEnvParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramEnvParameter4fvARB(GLenum _p0, GLuint _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameter4fvARB,glProgramEnvParameter4fvARB(_p0,_p1,_p2))
    glCalls().glProgramEnvParameter4fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glProgramEnvParameter4fvARB,glProgramEnvParameter4fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramEnvParameterI4iNV(GLenum _p0, GLuint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameterI4iNV,glProgramEnvParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramEnvParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramEnvParameterI4iNV,glProgramEnvParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramEnvParameterI4ivNV(GLenum _p0, GLuint _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameterI4ivNV,glProgramEnvParameterI4ivNV(_p0,_p1,_p2))
    glCalls().glProgramEnvParameterI4ivNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramEnvParameterI4ivNV,glProgramEnvParameterI4ivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramEnvParameterI4uiNV(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameterI4uiNV,glProgramEnvParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramEnvParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramEnvParameterI4uiNV,glProgramEnvParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramEnvParameterI4uivNV(GLenum _p0, GLuint _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameterI4uivNV,glProgramEnvParameterI4uivNV(_p0,_p1,_p2))
    glCalls().glProgramEnvParameterI4uivNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramEnvParameterI4uivNV,glProgramEnvParameterI4uivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramEnvParameters4fvEXT(GLenum _p0, GLuint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParameters4fvEXT,glProgramEnvParameters4fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramEnvParameters4fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramEnvParameters4fvEXT,glProgramEnvParameters4fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramEnvParametersI4ivNV(GLenum _p0, GLuint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParametersI4ivNV,glProgramEnvParametersI4ivNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramEnvParametersI4ivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramEnvParametersI4ivNV,glProgramEnvParametersI4ivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramEnvParametersI4uivNV(GLenum _p0, GLuint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramEnvParametersI4uivNV,glProgramEnvParametersI4uivNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramEnvParametersI4uivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramEnvParametersI4uivNV,glProgramEnvParametersI4uivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramLocalParameter4dARB(GLenum _p0, GLuint _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameter4dARB,glProgramLocalParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramLocalParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramLocalParameter4dARB,glProgramLocalParameter4dARB(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramLocalParameter4dvARB(GLenum _p0, GLuint _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameter4dvARB,glProgramLocalParameter4dvARB(_p0,_p1,_p2))
    glCalls().glProgramLocalParameter4dvARB(_p0,_p1,_p2);
    POST_USER_CALL(glProgramLocalParameter4dvARB,glProgramLocalParameter4dvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramLocalParameter4fARB(GLenum _p0, GLuint _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4, GLfloat _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameter4fARB,glProgramLocalParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramLocalParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramLocalParameter4fARB,glProgramLocalParameter4fARB(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramLocalParameter4fvARB(GLenum _p0, GLuint _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameter4fvARB,glProgramLocalParameter4fvARB(_p0,_p1,_p2))
    glCalls().glProgramLocalParameter4fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glProgramLocalParameter4fvARB,glProgramLocalParameter4fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramLocalParameterI4iNV(GLenum _p0, GLuint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameterI4iNV,glProgramLocalParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramLocalParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramLocalParameterI4iNV,glProgramLocalParameterI4iNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramLocalParameterI4ivNV(GLenum _p0, GLuint _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameterI4ivNV,glProgramLocalParameterI4ivNV(_p0,_p1,_p2))
    glCalls().glProgramLocalParameterI4ivNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramLocalParameterI4ivNV,glProgramLocalParameterI4ivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramLocalParameterI4uiNV(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameterI4uiNV,glProgramLocalParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramLocalParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramLocalParameterI4uiNV,glProgramLocalParameterI4uiNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramLocalParameterI4uivNV(GLenum _p0, GLuint _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameterI4uivNV,glProgramLocalParameterI4uivNV(_p0,_p1,_p2))
    glCalls().glProgramLocalParameterI4uivNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramLocalParameterI4uivNV,glProgramLocalParameterI4uivNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramLocalParameters4fvEXT(GLenum _p0, GLuint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParameters4fvEXT,glProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramLocalParameters4fvEXT,glProgramLocalParameters4fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramLocalParametersI4ivNV(GLenum _p0, GLuint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParametersI4ivNV,glProgramLocalParametersI4ivNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramLocalParametersI4ivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramLocalParametersI4ivNV,glProgramLocalParametersI4ivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramLocalParametersI4uivNV(GLenum _p0, GLuint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramLocalParametersI4uivNV,glProgramLocalParametersI4uivNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramLocalParametersI4uivNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramLocalParametersI4uivNV,glProgramLocalParametersI4uivNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramNamedParameter4dNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, GLdouble _p3, GLdouble _p4, GLdouble _p5, GLdouble _p6)
{
    gli().init();
    PREV_USER_CALL(glProgramNamedParameter4dNV,glProgramNamedParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glProgramNamedParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glProgramNamedParameter4dNV,glProgramNamedParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glProgramNamedParameter4dvNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, const GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramNamedParameter4dvNV,glProgramNamedParameter4dvNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramNamedParameter4dvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramNamedParameter4dvNV,glProgramNamedParameter4dvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramNamedParameter4fNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, GLfloat _p3, GLfloat _p4, GLfloat _p5, GLfloat _p6)
{
    gli().init();
    PREV_USER_CALL(glProgramNamedParameter4fNV,glProgramNamedParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glProgramNamedParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glProgramNamedParameter4fNV,glProgramNamedParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glProgramNamedParameter4fvNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramNamedParameter4fvNV,glProgramNamedParameter4fvNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramNamedParameter4fvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramNamedParameter4fvNV,glProgramNamedParameter4fvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramParameter4dNV(GLenum _p0, GLuint _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4, GLdouble _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramParameter4dNV,glProgramParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramParameter4dNV,glProgramParameter4dNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramParameter4dvNV(GLenum _p0, GLuint _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramParameter4dvNV,glProgramParameter4dvNV(_p0,_p1,_p2))
    glCalls().glProgramParameter4dvNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramParameter4dvNV,glProgramParameter4dvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramParameter4fNV(GLenum _p0, GLuint _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4, GLfloat _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramParameter4fNV,glProgramParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramParameter4fNV,glProgramParameter4fNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramParameter4fvNV(GLenum _p0, GLuint _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glProgramParameter4fvNV,glProgramParameter4fvNV(_p0,_p1,_p2))
    glCalls().glProgramParameter4fvNV(_p0,_p1,_p2);
    POST_USER_CALL(glProgramParameter4fvNV,glProgramParameter4fvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramParameteriARB(GLuint _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glProgramParameteriARB,glProgramParameteriARB(_p0,_p1,_p2))
    glCalls().glProgramParameteriARB(_p0,_p1,_p2);
    POST_USER_CALL(glProgramParameteriARB,glProgramParameteriARB(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramParameteriEXT(GLuint _p0, GLenum _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glProgramParameteriEXT,glProgramParameteriEXT(_p0,_p1,_p2))
    glCalls().glProgramParameteriEXT(_p0,_p1,_p2);
    POST_USER_CALL(glProgramParameteriEXT,glProgramParameteriEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramParameters4dvNV(GLenum _p0, GLuint _p1, GLuint _p2, const GLdouble *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramParameters4dvNV,glProgramParameters4dvNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramParameters4dvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramParameters4dvNV,glProgramParameters4dvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramParameters4fvNV(GLenum _p0, GLuint _p1, GLuint _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramParameters4fvNV,glProgramParameters4fvNV(_p0,_p1,_p2,_p3))
    glCalls().glProgramParameters4fvNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramParameters4fvNV,glProgramParameters4fvNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramStringARB(GLenum _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramStringARB,glProgramStringARB(_p0,_p1,_p2,_p3))
    glCalls().glProgramStringARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramStringARB,glProgramStringARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform1fEXT(GLuint _p0, GLint _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1fEXT,glProgramUniform1fEXT(_p0,_p1,_p2))
    glCalls().glProgramUniform1fEXT(_p0,_p1,_p2);
    POST_USER_CALL(glProgramUniform1fEXT,glProgramUniform1fEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramUniform1fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1fvEXT,glProgramUniform1fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform1fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform1fvEXT,glProgramUniform1fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform1iEXT(GLuint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1iEXT,glProgramUniform1iEXT(_p0,_p1,_p2))
    glCalls().glProgramUniform1iEXT(_p0,_p1,_p2);
    POST_USER_CALL(glProgramUniform1iEXT,glProgramUniform1iEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramUniform1ivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1ivEXT,glProgramUniform1ivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform1ivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform1ivEXT,glProgramUniform1ivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform1uiEXT(GLuint _p0, GLint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1uiEXT,glProgramUniform1uiEXT(_p0,_p1,_p2))
    glCalls().glProgramUniform1uiEXT(_p0,_p1,_p2);
    POST_USER_CALL(glProgramUniform1uiEXT,glProgramUniform1uiEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glProgramUniform1uivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform1uivEXT,glProgramUniform1uivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform1uivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform1uivEXT,glProgramUniform1uivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2fEXT(GLuint _p0, GLint _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2fEXT,glProgramUniform2fEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2fEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2fEXT,glProgramUniform2fEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2fvEXT,glProgramUniform2fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2fvEXT,glProgramUniform2fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2iEXT(GLuint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2iEXT,glProgramUniform2iEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2iEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2iEXT,glProgramUniform2iEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2ivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2ivEXT,glProgramUniform2ivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2ivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2ivEXT,glProgramUniform2ivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2uiEXT(GLuint _p0, GLint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2uiEXT,glProgramUniform2uiEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2uiEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2uiEXT,glProgramUniform2uiEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform2uivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform2uivEXT,glProgramUniform2uivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform2uivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform2uivEXT,glProgramUniform2uivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform3fEXT(GLuint _p0, GLint _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3fEXT,glProgramUniform3fEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniform3fEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniform3fEXT,glProgramUniform3fEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniform3fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3fvEXT,glProgramUniform3fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform3fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform3fvEXT,glProgramUniform3fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform3iEXT(GLuint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3iEXT,glProgramUniform3iEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniform3iEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniform3iEXT,glProgramUniform3iEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniform3ivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3ivEXT,glProgramUniform3ivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform3ivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform3ivEXT,glProgramUniform3ivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform3uiEXT(GLuint _p0, GLint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3uiEXT,glProgramUniform3uiEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniform3uiEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniform3uiEXT,glProgramUniform3uiEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniform3uivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform3uivEXT,glProgramUniform3uivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform3uivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform3uivEXT,glProgramUniform3uivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform4fEXT(GLuint _p0, GLint _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4, GLfloat _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4fEXT,glProgramUniform4fEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramUniform4fEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramUniform4fEXT,glProgramUniform4fEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramUniform4fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4fvEXT,glProgramUniform4fvEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform4fvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform4fvEXT,glProgramUniform4fvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform4iEXT(GLuint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4iEXT,glProgramUniform4iEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramUniform4iEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramUniform4iEXT,glProgramUniform4iEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramUniform4ivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4ivEXT,glProgramUniform4ivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform4ivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform4ivEXT,glProgramUniform4ivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniform4uiEXT(GLuint _p0, GLint _p1, GLuint _p2, GLuint _p3, GLuint _p4, GLuint _p5)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4uiEXT,glProgramUniform4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glProgramUniform4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glProgramUniform4uiEXT,glProgramUniform4uiEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glProgramUniform4uivEXT(GLuint _p0, GLint _p1, GLsizei _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glProgramUniform4uivEXT,glProgramUniform4uivEXT(_p0,_p1,_p2,_p3))
    glCalls().glProgramUniform4uivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glProgramUniform4uivEXT,glProgramUniform4uivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glProgramUniformMatrix2fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix2fvEXT,glProgramUniformMatrix2fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix2fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix2fvEXT,glProgramUniformMatrix2fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix2x3fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix2x3fvEXT,glProgramUniformMatrix2x3fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix2x3fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix2x3fvEXT,glProgramUniformMatrix2x3fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix2x4fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix2x4fvEXT,glProgramUniformMatrix2x4fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix2x4fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix2x4fvEXT,glProgramUniformMatrix2x4fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix3fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix3fvEXT,glProgramUniformMatrix3fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix3fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix3fvEXT,glProgramUniformMatrix3fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix3x2fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix3x2fvEXT,glProgramUniformMatrix3x2fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix3x2fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix3x2fvEXT,glProgramUniformMatrix3x2fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix3x4fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix3x4fvEXT,glProgramUniformMatrix3x4fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix3x4fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix3x4fvEXT,glProgramUniformMatrix3x4fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix4fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix4fvEXT,glProgramUniformMatrix4fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix4fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix4fvEXT,glProgramUniformMatrix4fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix4x2fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix4x2fvEXT,glProgramUniformMatrix4x2fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix4x2fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix4x2fvEXT,glProgramUniformMatrix4x2fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramUniformMatrix4x3fvEXT(GLuint _p0, GLint _p1, GLsizei _p2, GLboolean _p3, const GLfloat *_p4)
{
    gli().init();
    PREV_USER_CALL(glProgramUniformMatrix4x3fvEXT,glProgramUniformMatrix4x3fvEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glProgramUniformMatrix4x3fvEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glProgramUniformMatrix4x3fvEXT,glProgramUniformMatrix4x3fvEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glProgramVertexLimitNV(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glProgramVertexLimitNV,glProgramVertexLimitNV(_p0,_p1))
    glCalls().glProgramVertexLimitNV(_p0,_p1);
    POST_USER_CALL(glProgramVertexLimitNV,glProgramVertexLimitNV(_p0,_p1))
}

void GLAPIENTRY glProvokingVertexEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glProvokingVertexEXT,glProvokingVertexEXT(_p0))
    glCalls().glProvokingVertexEXT(_p0);
    POST_USER_CALL(glProvokingVertexEXT,glProvokingVertexEXT(_p0))
}

void GLAPIENTRY glPushAttrib(GLbitfield mask)
{
    gli().init();
    PREV_USER_CALL(glPushAttrib,glPushAttrib(mask))
    glCalls().glPushAttrib(mask);
    POST_USER_CALL(glPushAttrib,glPushAttrib(mask))
}

void GLAPIENTRY glPushClientAttrib(GLbitfield mask)
{
    gli().init();
    PREV_USER_CALL(glPushClientAttrib,glPushClientAttrib(mask))
    glCalls().glPushClientAttrib(mask);
    POST_USER_CALL(glPushClientAttrib,glPushClientAttrib(mask))
}

void GLAPIENTRY glPushClientAttribDefaultEXT(GLbitfield _p0)
{
    gli().init();
    PREV_USER_CALL(glPushClientAttribDefaultEXT,glPushClientAttribDefaultEXT(_p0))
    glCalls().glPushClientAttribDefaultEXT(_p0);
    POST_USER_CALL(glPushClientAttribDefaultEXT,glPushClientAttribDefaultEXT(_p0))
}

void GLAPIENTRY glPushMatrix()
{
    gli().init();
    PREV_USER_CALL(glPushMatrix,glPushMatrix())
    glCalls().glPushMatrix();
    POST_USER_CALL(glPushMatrix,glPushMatrix())
}

void GLAPIENTRY glPushName(GLuint name)
{
    gli().init();
    PREV_USER_CALL(glPushName,glPushName(name))
    glCalls().glPushName(name);
    POST_USER_CALL(glPushName,glPushName(name))
}

void GLAPIENTRY glRasterPos2d(GLdouble x, GLdouble y)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2d,glRasterPos2d(x,y))
    glCalls().glRasterPos2d(x,y);
    POST_USER_CALL(glRasterPos2d,glRasterPos2d(x,y))
}

void GLAPIENTRY glRasterPos2dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2dv,glRasterPos2dv(v))
    glCalls().glRasterPos2dv(v);
    POST_USER_CALL(glRasterPos2dv,glRasterPos2dv(v))
}

void GLAPIENTRY glRasterPos2f(GLfloat x, GLfloat y)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2f,glRasterPos2f(x,y))
    glCalls().glRasterPos2f(x,y);
    POST_USER_CALL(glRasterPos2f,glRasterPos2f(x,y))
}

void GLAPIENTRY glRasterPos2fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2fv,glRasterPos2fv(v))
    glCalls().glRasterPos2fv(v);
    POST_USER_CALL(glRasterPos2fv,glRasterPos2fv(v))
}

void GLAPIENTRY glRasterPos2i(GLint x, GLint y)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2i,glRasterPos2i(x,y))
    glCalls().glRasterPos2i(x,y);
    POST_USER_CALL(glRasterPos2i,glRasterPos2i(x,y))
}

void GLAPIENTRY glRasterPos2iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2iv,glRasterPos2iv(v))
    glCalls().glRasterPos2iv(v);
    POST_USER_CALL(glRasterPos2iv,glRasterPos2iv(v))
}

void GLAPIENTRY glRasterPos2s(GLshort x, GLshort y)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2s,glRasterPos2s(x,y))
    glCalls().glRasterPos2s(x,y);
    POST_USER_CALL(glRasterPos2s,glRasterPos2s(x,y))
}

void GLAPIENTRY glRasterPos2sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos2sv,glRasterPos2sv(v))
    glCalls().glRasterPos2sv(v);
    POST_USER_CALL(glRasterPos2sv,glRasterPos2sv(v))
}

void GLAPIENTRY glRasterPos3d(GLdouble x, GLdouble y, GLdouble z)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3d,glRasterPos3d(x,y,z))
    glCalls().glRasterPos3d(x,y,z);
    POST_USER_CALL(glRasterPos3d,glRasterPos3d(x,y,z))
}

void GLAPIENTRY glRasterPos3dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3dv,glRasterPos3dv(v))
    glCalls().glRasterPos3dv(v);
    POST_USER_CALL(glRasterPos3dv,glRasterPos3dv(v))
}

void GLAPIENTRY glRasterPos3f(GLfloat x, GLfloat y, GLfloat z)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3f,glRasterPos3f(x,y,z))
    glCalls().glRasterPos3f(x,y,z);
    POST_USER_CALL(glRasterPos3f,glRasterPos3f(x,y,z))
}

void GLAPIENTRY glRasterPos3fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3fv,glRasterPos3fv(v))
    glCalls().glRasterPos3fv(v);
    POST_USER_CALL(glRasterPos3fv,glRasterPos3fv(v))
}

void GLAPIENTRY glRasterPos3i(GLint x, GLint y, GLint z)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3i,glRasterPos3i(x,y,z))
    glCalls().glRasterPos3i(x,y,z);
    POST_USER_CALL(glRasterPos3i,glRasterPos3i(x,y,z))
}

void GLAPIENTRY glRasterPos3iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3iv,glRasterPos3iv(v))
    glCalls().glRasterPos3iv(v);
    POST_USER_CALL(glRasterPos3iv,glRasterPos3iv(v))
}

void GLAPIENTRY glRasterPos3s(GLshort x, GLshort y, GLshort z)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3s,glRasterPos3s(x,y,z))
    glCalls().glRasterPos3s(x,y,z);
    POST_USER_CALL(glRasterPos3s,glRasterPos3s(x,y,z))
}

void GLAPIENTRY glRasterPos3sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos3sv,glRasterPos3sv(v))
    glCalls().glRasterPos3sv(v);
    POST_USER_CALL(glRasterPos3sv,glRasterPos3sv(v))
}

void GLAPIENTRY glRasterPos4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4d,glRasterPos4d(x,y,z,w))
    glCalls().glRasterPos4d(x,y,z,w);
    POST_USER_CALL(glRasterPos4d,glRasterPos4d(x,y,z,w))
}

void GLAPIENTRY glRasterPos4dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4dv,glRasterPos4dv(v))
    glCalls().glRasterPos4dv(v);
    POST_USER_CALL(glRasterPos4dv,glRasterPos4dv(v))
}

void GLAPIENTRY glRasterPos4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4f,glRasterPos4f(x,y,z,w))
    glCalls().glRasterPos4f(x,y,z,w);
    POST_USER_CALL(glRasterPos4f,glRasterPos4f(x,y,z,w))
}

void GLAPIENTRY glRasterPos4fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4fv,glRasterPos4fv(v))
    glCalls().glRasterPos4fv(v);
    POST_USER_CALL(glRasterPos4fv,glRasterPos4fv(v))
}

void GLAPIENTRY glRasterPos4i(GLint x, GLint y, GLint z, GLint w)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4i,glRasterPos4i(x,y,z,w))
    glCalls().glRasterPos4i(x,y,z,w);
    POST_USER_CALL(glRasterPos4i,glRasterPos4i(x,y,z,w))
}

void GLAPIENTRY glRasterPos4iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4iv,glRasterPos4iv(v))
    glCalls().glRasterPos4iv(v);
    POST_USER_CALL(glRasterPos4iv,glRasterPos4iv(v))
}

void GLAPIENTRY glRasterPos4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4s,glRasterPos4s(x,y,z,w))
    glCalls().glRasterPos4s(x,y,z,w);
    POST_USER_CALL(glRasterPos4s,glRasterPos4s(x,y,z,w))
}

void GLAPIENTRY glRasterPos4sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glRasterPos4sv,glRasterPos4sv(v))
    glCalls().glRasterPos4sv(v);
    POST_USER_CALL(glRasterPos4sv,glRasterPos4sv(v))
}

void GLAPIENTRY glReadBuffer(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glReadBuffer,glReadBuffer(mode))
    glCalls().glReadBuffer(mode);
    POST_USER_CALL(glReadBuffer,glReadBuffer(mode))
}

void GLAPIENTRY glReadInstrumentsSGIX(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glReadInstrumentsSGIX,glReadInstrumentsSGIX(_p0))
    glCalls().glReadInstrumentsSGIX(_p0);
    POST_USER_CALL(glReadInstrumentsSGIX,glReadInstrumentsSGIX(_p0))
}

void GLAPIENTRY glReadPixels(GLint x, GLint y, GLsizei width, GLsizei height, GLenum format, GLenum type, GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glReadPixels,glReadPixels(x,y,width,height,format,type,pixels))
    glCalls().glReadPixels(x,y,width,height,format,type,pixels);
    POST_USER_CALL(glReadPixels,glReadPixels(x,y,width,height,format,type,pixels))
}

void GLAPIENTRY glRectd(GLdouble x1, GLdouble y1, GLdouble x2, GLdouble y2)
{
    gli().init();
    PREV_USER_CALL(glRectd,glRectd(x1,y1,x2,y2))
    glCalls().glRectd(x1,y1,x2,y2);
    POST_USER_CALL(glRectd,glRectd(x1,y1,x2,y2))
}

void GLAPIENTRY glRectdv(const GLdouble *v1, const GLdouble *v2)
{
    gli().init();
    PREV_USER_CALL(glRectdv,glRectdv(v1,v2))
    glCalls().glRectdv(v1,v2);
    POST_USER_CALL(glRectdv,glRectdv(v1,v2))
}

void GLAPIENTRY glRectf(GLfloat x1, GLfloat y1, GLfloat x2, GLfloat y2)
{
    gli().init();
    PREV_USER_CALL(glRectf,glRectf(x1,y1,x2,y2))
    glCalls().glRectf(x1,y1,x2,y2);
    POST_USER_CALL(glRectf,glRectf(x1,y1,x2,y2))
}

void GLAPIENTRY glRectfv(const GLfloat *v1, const GLfloat *v2)
{
    gli().init();
    PREV_USER_CALL(glRectfv,glRectfv(v1,v2))
    glCalls().glRectfv(v1,v2);
    POST_USER_CALL(glRectfv,glRectfv(v1,v2))
}

void GLAPIENTRY glRecti(GLint x1, GLint y1, GLint x2, GLint y2)
{
    gli().init();
    PREV_USER_CALL(glRecti,glRecti(x1,y1,x2,y2))
    glCalls().glRecti(x1,y1,x2,y2);
    POST_USER_CALL(glRecti,glRecti(x1,y1,x2,y2))
}

void GLAPIENTRY glRectiv(const GLint *v1, const GLint *v2)
{
    gli().init();
    PREV_USER_CALL(glRectiv,glRectiv(v1,v2))
    glCalls().glRectiv(v1,v2);
    POST_USER_CALL(glRectiv,glRectiv(v1,v2))
}

void GLAPIENTRY glRects(GLshort x1, GLshort y1, GLshort x2, GLshort y2)
{
    gli().init();
    PREV_USER_CALL(glRects,glRects(x1,y1,x2,y2))
    glCalls().glRects(x1,y1,x2,y2);
    POST_USER_CALL(glRects,glRects(x1,y1,x2,y2))
}

void GLAPIENTRY glRectsv(const GLshort *v1, const GLshort *v2)
{
    gli().init();
    PREV_USER_CALL(glRectsv,glRectsv(v1,v2))
    glCalls().glRectsv(v1,v2);
    POST_USER_CALL(glRectsv,glRectsv(v1,v2))
}

void GLAPIENTRY glReferencePlaneSGIX(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glReferencePlaneSGIX,glReferencePlaneSGIX(_p0))
    glCalls().glReferencePlaneSGIX(_p0);
    POST_USER_CALL(glReferencePlaneSGIX,glReferencePlaneSGIX(_p0))
}

GLint GLAPIENTRY glRenderMode(GLenum mode)
{
    gli().init();
    GLint _result;
    PREV_USER_CALL(glRenderMode,glRenderMode(mode))
    _result = glCalls().glRenderMode(mode);
    POST_USER_CALL(glRenderMode,glRenderMode(mode))
    return _result;
}

void GLAPIENTRY glRenderbufferStorage(GLenum _p0, GLenum _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glRenderbufferStorage,glRenderbufferStorage(_p0,_p1,_p2,_p3))
    glCalls().glRenderbufferStorage(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glRenderbufferStorage,glRenderbufferStorage(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glRenderbufferStorageEXT(GLenum _p0, GLenum _p1, GLsizei _p2, GLsizei _p3)
{
    gli().init();
    PREV_USER_CALL(glRenderbufferStorageEXT,glRenderbufferStorageEXT(_p0,_p1,_p2,_p3))
    glCalls().glRenderbufferStorageEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glRenderbufferStorageEXT,glRenderbufferStorageEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glRenderbufferStorageMultisample(GLenum _p0, GLsizei _p1, GLenum _p2, GLsizei _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glRenderbufferStorageMultisample,glRenderbufferStorageMultisample(_p0,_p1,_p2,_p3,_p4))
    glCalls().glRenderbufferStorageMultisample(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glRenderbufferStorageMultisample,glRenderbufferStorageMultisample(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glRenderbufferStorageMultisampleCoverageNV(GLenum _p0, GLsizei _p1, GLsizei _p2, GLenum _p3, GLsizei _p4, GLsizei _p5)
{
    gli().init();
    PREV_USER_CALL(glRenderbufferStorageMultisampleCoverageNV,glRenderbufferStorageMultisampleCoverageNV(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glRenderbufferStorageMultisampleCoverageNV(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glRenderbufferStorageMultisampleCoverageNV,glRenderbufferStorageMultisampleCoverageNV(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glRenderbufferStorageMultisampleEXT(GLenum _p0, GLsizei _p1, GLenum _p2, GLsizei _p3, GLsizei _p4)
{
    gli().init();
    PREV_USER_CALL(glRenderbufferStorageMultisampleEXT,glRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glRenderbufferStorageMultisampleEXT,glRenderbufferStorageMultisampleEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glRequestResidentProgramsNV(GLsizei _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glRequestResidentProgramsNV,glRequestResidentProgramsNV(_p0,_p1))
    glCalls().glRequestResidentProgramsNV(_p0,_p1);
    POST_USER_CALL(glRequestResidentProgramsNV,glRequestResidentProgramsNV(_p0,_p1))
}

void GLAPIENTRY glResetHistogram(GLenum target)
{
    gli().init();
    PREV_USER_CALL(glResetHistogram,glResetHistogram(target))
    glCalls().glResetHistogram(target);
    POST_USER_CALL(glResetHistogram,glResetHistogram(target))
}

void GLAPIENTRY glResetHistogramEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glResetHistogramEXT,glResetHistogramEXT(_p0))
    glCalls().glResetHistogramEXT(_p0);
    POST_USER_CALL(glResetHistogramEXT,glResetHistogramEXT(_p0))
}

void GLAPIENTRY glResetMinmax(GLenum target)
{
    gli().init();
    PREV_USER_CALL(glResetMinmax,glResetMinmax(target))
    glCalls().glResetMinmax(target);
    POST_USER_CALL(glResetMinmax,glResetMinmax(target))
}

void GLAPIENTRY glResetMinmaxEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glResetMinmaxEXT,glResetMinmaxEXT(_p0))
    glCalls().glResetMinmaxEXT(_p0);
    POST_USER_CALL(glResetMinmaxEXT,glResetMinmaxEXT(_p0))
}

void GLAPIENTRY glResumeTransformFeedbackNV()
{
    gli().init();
    PREV_USER_CALL(glResumeTransformFeedbackNV,glResumeTransformFeedbackNV())
    glCalls().glResumeTransformFeedbackNV();
    POST_USER_CALL(glResumeTransformFeedbackNV,glResumeTransformFeedbackNV())
}

void GLAPIENTRY glRotated(GLdouble angle, GLdouble x, GLdouble y, GLdouble z)
{
    gli().init();
    PREV_USER_CALL(glRotated,glRotated(angle,x,y,z))
    glCalls().glRotated(angle,x,y,z);
    POST_USER_CALL(glRotated,glRotated(angle,x,y,z))
}

void GLAPIENTRY glRotatef(GLfloat angle, GLfloat x, GLfloat y, GLfloat z)
{
    gli().init();
    PREV_USER_CALL(glRotatef,glRotatef(angle,x,y,z))
    glCalls().glRotatef(angle,x,y,z);
    POST_USER_CALL(glRotatef,glRotatef(angle,x,y,z))
}

void GLAPIENTRY glSampleCoverage(GLclampf value, GLboolean invert)
{
    gli().init();
    PREV_USER_CALL(glSampleCoverage,glSampleCoverage(value,invert))
    glCalls().glSampleCoverage(value,invert);
    POST_USER_CALL(glSampleCoverage,glSampleCoverage(value,invert))
}

void GLAPIENTRY glSampleCoverageARB(GLclampf _p0, GLboolean _p1)
{
    gli().init();
    PREV_USER_CALL(glSampleCoverageARB,glSampleCoverageARB(_p0,_p1))
    glCalls().glSampleCoverageARB(_p0,_p1);
    POST_USER_CALL(glSampleCoverageARB,glSampleCoverageARB(_p0,_p1))
}

void GLAPIENTRY glSampleMapATI(GLuint _p0, GLuint _p1, GLenum _p2)
{
    gli().init();
    PREV_USER_CALL(glSampleMapATI,glSampleMapATI(_p0,_p1,_p2))
    glCalls().glSampleMapATI(_p0,_p1,_p2);
    POST_USER_CALL(glSampleMapATI,glSampleMapATI(_p0,_p1,_p2))
}

void GLAPIENTRY glSampleMaskEXT(GLclampf _p0, GLboolean _p1)
{
    gli().init();
    PREV_USER_CALL(glSampleMaskEXT,glSampleMaskEXT(_p0,_p1))
    glCalls().glSampleMaskEXT(_p0,_p1);
    POST_USER_CALL(glSampleMaskEXT,glSampleMaskEXT(_p0,_p1))
}

void GLAPIENTRY glSampleMaskIndexedNV(GLuint _p0, GLbitfield _p1)
{
    gli().init();
    PREV_USER_CALL(glSampleMaskIndexedNV,glSampleMaskIndexedNV(_p0,_p1))
    glCalls().glSampleMaskIndexedNV(_p0,_p1);
    POST_USER_CALL(glSampleMaskIndexedNV,glSampleMaskIndexedNV(_p0,_p1))
}

void GLAPIENTRY glSampleMaskSGIS(GLclampf _p0, GLboolean _p1)
{
    gli().init();
    PREV_USER_CALL(glSampleMaskSGIS,glSampleMaskSGIS(_p0,_p1))
    glCalls().glSampleMaskSGIS(_p0,_p1);
    POST_USER_CALL(glSampleMaskSGIS,glSampleMaskSGIS(_p0,_p1))
}

void GLAPIENTRY glSamplePatternEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glSamplePatternEXT,glSamplePatternEXT(_p0))
    glCalls().glSamplePatternEXT(_p0);
    POST_USER_CALL(glSamplePatternEXT,glSamplePatternEXT(_p0))
}

void GLAPIENTRY glSamplePatternSGIS(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glSamplePatternSGIS,glSamplePatternSGIS(_p0))
    glCalls().glSamplePatternSGIS(_p0);
    POST_USER_CALL(glSamplePatternSGIS,glSamplePatternSGIS(_p0))
}

void GLAPIENTRY glScaled(GLdouble x, GLdouble y, GLdouble z)
{
    gli().init();
    PREV_USER_CALL(glScaled,glScaled(x,y,z))
    glCalls().glScaled(x,y,z);
    POST_USER_CALL(glScaled,glScaled(x,y,z))
}

void GLAPIENTRY glScalef(GLfloat x, GLfloat y, GLfloat z)
{
    gli().init();
    PREV_USER_CALL(glScalef,glScalef(x,y,z))
    glCalls().glScalef(x,y,z);
    POST_USER_CALL(glScalef,glScalef(x,y,z))
}

void GLAPIENTRY glScissor(GLint x, GLint y, GLsizei width, GLsizei height)
{
    gli().init();
    PREV_USER_CALL(glScissor,glScissor(x,y,width,height))
    glCalls().glScissor(x,y,width,height);
    POST_USER_CALL(glScissor,glScissor(x,y,width,height))
}

void GLAPIENTRY glSecondaryColor3b(GLbyte _p0, GLbyte _p1, GLbyte _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3b,glSecondaryColor3b(_p0,_p1,_p2))
    glCalls().glSecondaryColor3b(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3b,glSecondaryColor3b(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3bEXT(GLbyte _p0, GLbyte _p1, GLbyte _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3bEXT,glSecondaryColor3bEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3bEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3bEXT,glSecondaryColor3bEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3bv(const GLbyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3bv,glSecondaryColor3bv(_p0))
    glCalls().glSecondaryColor3bv(_p0);
    POST_USER_CALL(glSecondaryColor3bv,glSecondaryColor3bv(_p0))
}

void GLAPIENTRY glSecondaryColor3bvEXT(const GLbyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3bvEXT,glSecondaryColor3bvEXT(_p0))
    glCalls().glSecondaryColor3bvEXT(_p0);
    POST_USER_CALL(glSecondaryColor3bvEXT,glSecondaryColor3bvEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3d(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3d,glSecondaryColor3d(_p0,_p1,_p2))
    glCalls().glSecondaryColor3d(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3d,glSecondaryColor3d(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3dEXT(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3dEXT,glSecondaryColor3dEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3dEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3dEXT,glSecondaryColor3dEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3dv(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3dv,glSecondaryColor3dv(_p0))
    glCalls().glSecondaryColor3dv(_p0);
    POST_USER_CALL(glSecondaryColor3dv,glSecondaryColor3dv(_p0))
}

void GLAPIENTRY glSecondaryColor3dvEXT(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3dvEXT,glSecondaryColor3dvEXT(_p0))
    glCalls().glSecondaryColor3dvEXT(_p0);
    POST_USER_CALL(glSecondaryColor3dvEXT,glSecondaryColor3dvEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3f(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3f,glSecondaryColor3f(_p0,_p1,_p2))
    glCalls().glSecondaryColor3f(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3f,glSecondaryColor3f(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3fEXT(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3fEXT,glSecondaryColor3fEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3fEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3fEXT,glSecondaryColor3fEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3fv(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3fv,glSecondaryColor3fv(_p0))
    glCalls().glSecondaryColor3fv(_p0);
    POST_USER_CALL(glSecondaryColor3fv,glSecondaryColor3fv(_p0))
}

void GLAPIENTRY glSecondaryColor3fvEXT(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3fvEXT,glSecondaryColor3fvEXT(_p0))
    glCalls().glSecondaryColor3fvEXT(_p0);
    POST_USER_CALL(glSecondaryColor3fvEXT,glSecondaryColor3fvEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3hNV,glSecondaryColor3hNV(_p0,_p1,_p2))
    glCalls().glSecondaryColor3hNV(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3hNV,glSecondaryColor3hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3hvNV,glSecondaryColor3hvNV(_p0))
    glCalls().glSecondaryColor3hvNV(_p0);
    POST_USER_CALL(glSecondaryColor3hvNV,glSecondaryColor3hvNV(_p0))
}

void GLAPIENTRY glSecondaryColor3i(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3i,glSecondaryColor3i(_p0,_p1,_p2))
    glCalls().glSecondaryColor3i(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3i,glSecondaryColor3i(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3iEXT(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3iEXT,glSecondaryColor3iEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3iEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3iEXT,glSecondaryColor3iEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3iv(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3iv,glSecondaryColor3iv(_p0))
    glCalls().glSecondaryColor3iv(_p0);
    POST_USER_CALL(glSecondaryColor3iv,glSecondaryColor3iv(_p0))
}

void GLAPIENTRY glSecondaryColor3ivEXT(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ivEXT,glSecondaryColor3ivEXT(_p0))
    glCalls().glSecondaryColor3ivEXT(_p0);
    POST_USER_CALL(glSecondaryColor3ivEXT,glSecondaryColor3ivEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3s(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3s,glSecondaryColor3s(_p0,_p1,_p2))
    glCalls().glSecondaryColor3s(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3s,glSecondaryColor3s(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3sEXT(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3sEXT,glSecondaryColor3sEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3sEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3sEXT,glSecondaryColor3sEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3sv(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3sv,glSecondaryColor3sv(_p0))
    glCalls().glSecondaryColor3sv(_p0);
    POST_USER_CALL(glSecondaryColor3sv,glSecondaryColor3sv(_p0))
}

void GLAPIENTRY glSecondaryColor3svEXT(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3svEXT,glSecondaryColor3svEXT(_p0))
    glCalls().glSecondaryColor3svEXT(_p0);
    POST_USER_CALL(glSecondaryColor3svEXT,glSecondaryColor3svEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3ub(GLubyte _p0, GLubyte _p1, GLubyte _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ub,glSecondaryColor3ub(_p0,_p1,_p2))
    glCalls().glSecondaryColor3ub(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3ub,glSecondaryColor3ub(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3ubEXT(GLubyte _p0, GLubyte _p1, GLubyte _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ubEXT,glSecondaryColor3ubEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3ubEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3ubEXT,glSecondaryColor3ubEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3ubv(const GLubyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ubv,glSecondaryColor3ubv(_p0))
    glCalls().glSecondaryColor3ubv(_p0);
    POST_USER_CALL(glSecondaryColor3ubv,glSecondaryColor3ubv(_p0))
}

void GLAPIENTRY glSecondaryColor3ubvEXT(const GLubyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ubvEXT,glSecondaryColor3ubvEXT(_p0))
    glCalls().glSecondaryColor3ubvEXT(_p0);
    POST_USER_CALL(glSecondaryColor3ubvEXT,glSecondaryColor3ubvEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3ui(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3ui,glSecondaryColor3ui(_p0,_p1,_p2))
    glCalls().glSecondaryColor3ui(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3ui,glSecondaryColor3ui(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3uiEXT(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3uiEXT,glSecondaryColor3uiEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3uiEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3uiEXT,glSecondaryColor3uiEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3uiv(const GLuint *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3uiv,glSecondaryColor3uiv(_p0))
    glCalls().glSecondaryColor3uiv(_p0);
    POST_USER_CALL(glSecondaryColor3uiv,glSecondaryColor3uiv(_p0))
}

void GLAPIENTRY glSecondaryColor3uivEXT(const GLuint *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3uivEXT,glSecondaryColor3uivEXT(_p0))
    glCalls().glSecondaryColor3uivEXT(_p0);
    POST_USER_CALL(glSecondaryColor3uivEXT,glSecondaryColor3uivEXT(_p0))
}

void GLAPIENTRY glSecondaryColor3us(GLushort _p0, GLushort _p1, GLushort _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3us,glSecondaryColor3us(_p0,_p1,_p2))
    glCalls().glSecondaryColor3us(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3us,glSecondaryColor3us(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3usEXT(GLushort _p0, GLushort _p1, GLushort _p2)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3usEXT,glSecondaryColor3usEXT(_p0,_p1,_p2))
    glCalls().glSecondaryColor3usEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSecondaryColor3usEXT,glSecondaryColor3usEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSecondaryColor3usv(const GLushort *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3usv,glSecondaryColor3usv(_p0))
    glCalls().glSecondaryColor3usv(_p0);
    POST_USER_CALL(glSecondaryColor3usv,glSecondaryColor3usv(_p0))
}

void GLAPIENTRY glSecondaryColor3usvEXT(const GLushort *_p0)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColor3usvEXT,glSecondaryColor3usvEXT(_p0))
    glCalls().glSecondaryColor3usvEXT(_p0);
    POST_USER_CALL(glSecondaryColor3usvEXT,glSecondaryColor3usvEXT(_p0))
}

void GLAPIENTRY glSecondaryColorPointer(GLint _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColorPointer,glSecondaryColorPointer(_p0,_p1,_p2,_p3))
    glCalls().glSecondaryColorPointer(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glSecondaryColorPointer,glSecondaryColorPointer(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glSecondaryColorPointerEXT(GLint _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glSecondaryColorPointerEXT,glSecondaryColorPointerEXT(_p0,_p1,_p2,_p3))
    glCalls().glSecondaryColorPointerEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glSecondaryColorPointerEXT,glSecondaryColorPointerEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glSelectBuffer(GLsizei size, GLuint *buffer)
{
    gli().init();
    PREV_USER_CALL(glSelectBuffer,glSelectBuffer(size,buffer))
    glCalls().glSelectBuffer(size,buffer);
    POST_USER_CALL(glSelectBuffer,glSelectBuffer(size,buffer))
}

void GLAPIENTRY glSelectPerfMonitorCountersAMD(GLuint _p0, GLboolean _p1, GLuint _p2, GLint _p3, GLuint *_p4)
{
    gli().init();
    PREV_USER_CALL(glSelectPerfMonitorCountersAMD,glSelectPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4))
    glCalls().glSelectPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glSelectPerfMonitorCountersAMD,glSelectPerfMonitorCountersAMD(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glSeparableFilter2D(GLenum target, GLenum internalformat, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *row, const GLvoid *column)
{
    gli().init();
    PREV_USER_CALL(glSeparableFilter2D,glSeparableFilter2D(target,internalformat,width,height,format,type,row,column))
    glCalls().glSeparableFilter2D(target,internalformat,width,height,format,type,row,column);
    POST_USER_CALL(glSeparableFilter2D,glSeparableFilter2D(target,internalformat,width,height,format,type,row,column))
}

void GLAPIENTRY glSeparableFilter2DEXT(GLenum _p0, GLenum _p1, GLsizei _p2, GLsizei _p3, GLenum _p4, GLenum _p5, const GLvoid *_p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glSeparableFilter2DEXT,glSeparableFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glSeparableFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glSeparableFilter2DEXT,glSeparableFilter2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glSetFenceAPPLE(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glSetFenceAPPLE,glSetFenceAPPLE(_p0))
    glCalls().glSetFenceAPPLE(_p0);
    POST_USER_CALL(glSetFenceAPPLE,glSetFenceAPPLE(_p0))
}

void GLAPIENTRY glSetFenceNV(GLuint _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glSetFenceNV,glSetFenceNV(_p0,_p1))
    glCalls().glSetFenceNV(_p0,_p1);
    POST_USER_CALL(glSetFenceNV,glSetFenceNV(_p0,_p1))
}

void GLAPIENTRY glSetFragmentShaderConstantATI(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glSetFragmentShaderConstantATI,glSetFragmentShaderConstantATI(_p0,_p1))
    glCalls().glSetFragmentShaderConstantATI(_p0,_p1);
    POST_USER_CALL(glSetFragmentShaderConstantATI,glSetFragmentShaderConstantATI(_p0,_p1))
}

void GLAPIENTRY glSetInvariantEXT(GLuint _p0, GLenum _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glSetInvariantEXT,glSetInvariantEXT(_p0,_p1,_p2))
    glCalls().glSetInvariantEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSetInvariantEXT,glSetInvariantEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glSetLocalConstantEXT(GLuint _p0, GLenum _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glSetLocalConstantEXT,glSetLocalConstantEXT(_p0,_p1,_p2))
    glCalls().glSetLocalConstantEXT(_p0,_p1,_p2);
    POST_USER_CALL(glSetLocalConstantEXT,glSetLocalConstantEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glShadeModel(GLenum mode)
{
    gli().init();
    PREV_USER_CALL(glShadeModel,glShadeModel(mode))
    glCalls().glShadeModel(mode);
    POST_USER_CALL(glShadeModel,glShadeModel(mode))
}

void GLAPIENTRY glShaderOp1EXT(GLenum _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glShaderOp1EXT,glShaderOp1EXT(_p0,_p1,_p2))
    glCalls().glShaderOp1EXT(_p0,_p1,_p2);
    POST_USER_CALL(glShaderOp1EXT,glShaderOp1EXT(_p0,_p1,_p2))
}

void GLAPIENTRY glShaderOp2EXT(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glShaderOp2EXT,glShaderOp2EXT(_p0,_p1,_p2,_p3))
    glCalls().glShaderOp2EXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glShaderOp2EXT,glShaderOp2EXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glShaderOp3EXT(GLenum _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glShaderOp3EXT,glShaderOp3EXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glShaderOp3EXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glShaderOp3EXT,glShaderOp3EXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glShaderSource(GLuint _p0, GLsizei _p1, const GLchar **_p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glShaderSource,glShaderSource(_p0,_p1,_p2,_p3))
    glCalls().glShaderSource(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glShaderSource,glShaderSource(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glShaderSourceARB(GLhandleARB _p0, GLsizei _p1, const GLcharARB **_p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glShaderSourceARB,glShaderSourceARB(_p0,_p1,_p2,_p3))
    glCalls().glShaderSourceARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glShaderSourceARB,glShaderSourceARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glSharpenTexFuncSGIS(GLenum _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glSharpenTexFuncSGIS,glSharpenTexFuncSGIS(_p0,_p1,_p2))
    glCalls().glSharpenTexFuncSGIS(_p0,_p1,_p2);
    POST_USER_CALL(glSharpenTexFuncSGIS,glSharpenTexFuncSGIS(_p0,_p1,_p2))
}

void GLAPIENTRY glSpriteParameterfSGIX(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glSpriteParameterfSGIX,glSpriteParameterfSGIX(_p0,_p1))
    glCalls().glSpriteParameterfSGIX(_p0,_p1);
    POST_USER_CALL(glSpriteParameterfSGIX,glSpriteParameterfSGIX(_p0,_p1))
}

void GLAPIENTRY glSpriteParameterfvSGIX(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glSpriteParameterfvSGIX,glSpriteParameterfvSGIX(_p0,_p1))
    glCalls().glSpriteParameterfvSGIX(_p0,_p1);
    POST_USER_CALL(glSpriteParameterfvSGIX,glSpriteParameterfvSGIX(_p0,_p1))
}

void GLAPIENTRY glSpriteParameteriSGIX(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glSpriteParameteriSGIX,glSpriteParameteriSGIX(_p0,_p1))
    glCalls().glSpriteParameteriSGIX(_p0,_p1);
    POST_USER_CALL(glSpriteParameteriSGIX,glSpriteParameteriSGIX(_p0,_p1))
}

void GLAPIENTRY glSpriteParameterivSGIX(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glSpriteParameterivSGIX,glSpriteParameterivSGIX(_p0,_p1))
    glCalls().glSpriteParameterivSGIX(_p0,_p1);
    POST_USER_CALL(glSpriteParameterivSGIX,glSpriteParameterivSGIX(_p0,_p1))
}

void GLAPIENTRY glStartInstrumentsSGIX()
{
    gli().init();
    PREV_USER_CALL(glStartInstrumentsSGIX,glStartInstrumentsSGIX())
    glCalls().glStartInstrumentsSGIX();
    POST_USER_CALL(glStartInstrumentsSGIX,glStartInstrumentsSGIX())
}

void GLAPIENTRY glStencilClearTagEXT(GLsizei _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glStencilClearTagEXT,glStencilClearTagEXT(_p0,_p1))
    glCalls().glStencilClearTagEXT(_p0,_p1);
    POST_USER_CALL(glStencilClearTagEXT,glStencilClearTagEXT(_p0,_p1))
}

void GLAPIENTRY glStencilFunc(GLenum func, GLint ref, GLuint mask)
{
    gli().init();
    PREV_USER_CALL(glStencilFunc,glStencilFunc(func,ref,mask))
    glCalls().glStencilFunc(func,ref,mask);
    POST_USER_CALL(glStencilFunc,glStencilFunc(func,ref,mask))
}

void GLAPIENTRY glStencilFuncSeparate(GLenum _p0, GLenum _p1, GLint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glStencilFuncSeparate,glStencilFuncSeparate(_p0,_p1,_p2,_p3))
    glCalls().glStencilFuncSeparate(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glStencilFuncSeparate,glStencilFuncSeparate(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glStencilFuncSeparateATI(GLenum _p0, GLenum _p1, GLint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glStencilFuncSeparateATI,glStencilFuncSeparateATI(_p0,_p1,_p2,_p3))
    glCalls().glStencilFuncSeparateATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glStencilFuncSeparateATI,glStencilFuncSeparateATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glStencilMask(GLuint mask)
{
    gli().init();
    PREV_USER_CALL(glStencilMask,glStencilMask(mask))
    glCalls().glStencilMask(mask);
    POST_USER_CALL(glStencilMask,glStencilMask(mask))
}

void GLAPIENTRY glStencilMaskSeparate(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glStencilMaskSeparate,glStencilMaskSeparate(_p0,_p1))
    glCalls().glStencilMaskSeparate(_p0,_p1);
    POST_USER_CALL(glStencilMaskSeparate,glStencilMaskSeparate(_p0,_p1))
}

void GLAPIENTRY glStencilOp(GLenum fail, GLenum zfail, GLenum zpass)
{
    gli().init();
    PREV_USER_CALL(glStencilOp,glStencilOp(fail,zfail,zpass))
    glCalls().glStencilOp(fail,zfail,zpass);
    POST_USER_CALL(glStencilOp,glStencilOp(fail,zfail,zpass))
}

void GLAPIENTRY glStencilOpSeparate(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glStencilOpSeparate,glStencilOpSeparate(_p0,_p1,_p2,_p3))
    glCalls().glStencilOpSeparate(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glStencilOpSeparate,glStencilOpSeparate(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glStencilOpSeparateATI(GLenum _p0, GLenum _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glStencilOpSeparateATI,glStencilOpSeparateATI(_p0,_p1,_p2,_p3))
    glCalls().glStencilOpSeparateATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glStencilOpSeparateATI,glStencilOpSeparateATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glStopInstrumentsSGIX(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glStopInstrumentsSGIX,glStopInstrumentsSGIX(_p0))
    glCalls().glStopInstrumentsSGIX(_p0);
    POST_USER_CALL(glStopInstrumentsSGIX,glStopInstrumentsSGIX(_p0))
}

void GLAPIENTRY glStringMarkerGREMEDY(GLsizei _p0, const GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glStringMarkerGREMEDY,glStringMarkerGREMEDY(_p0,_p1))
    glCalls().glStringMarkerGREMEDY(_p0,_p1);
    POST_USER_CALL(glStringMarkerGREMEDY,glStringMarkerGREMEDY(_p0,_p1))
}

void GLAPIENTRY glSwizzleEXT(GLuint _p0, GLuint _p1, GLenum _p2, GLenum _p3, GLenum _p4, GLenum _p5)
{
    gli().init();
    PREV_USER_CALL(glSwizzleEXT,glSwizzleEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glSwizzleEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glSwizzleEXT,glSwizzleEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glTagSampleBufferSGIX()
{
    gli().init();
    PREV_USER_CALL(glTagSampleBufferSGIX,glTagSampleBufferSGIX())
    glCalls().glTagSampleBufferSGIX();
    POST_USER_CALL(glTagSampleBufferSGIX,glTagSampleBufferSGIX())
}

void GLAPIENTRY glTangent3bEXT(GLbyte _p0, GLbyte _p1, GLbyte _p2)
{
    gli().init();
    PREV_USER_CALL(glTangent3bEXT,glTangent3bEXT(_p0,_p1,_p2))
    glCalls().glTangent3bEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangent3bEXT,glTangent3bEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTangent3bvEXT(const GLbyte *_p0)
{
    gli().init();
    PREV_USER_CALL(glTangent3bvEXT,glTangent3bvEXT(_p0))
    glCalls().glTangent3bvEXT(_p0);
    POST_USER_CALL(glTangent3bvEXT,glTangent3bvEXT(_p0))
}

void GLAPIENTRY glTangent3dEXT(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glTangent3dEXT,glTangent3dEXT(_p0,_p1,_p2))
    glCalls().glTangent3dEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangent3dEXT,glTangent3dEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTangent3dvEXT(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glTangent3dvEXT,glTangent3dvEXT(_p0))
    glCalls().glTangent3dvEXT(_p0);
    POST_USER_CALL(glTangent3dvEXT,glTangent3dvEXT(_p0))
}

void GLAPIENTRY glTangent3fEXT(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glTangent3fEXT,glTangent3fEXT(_p0,_p1,_p2))
    glCalls().glTangent3fEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangent3fEXT,glTangent3fEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTangent3fvEXT(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glTangent3fvEXT,glTangent3fvEXT(_p0))
    glCalls().glTangent3fvEXT(_p0);
    POST_USER_CALL(glTangent3fvEXT,glTangent3fvEXT(_p0))
}

void GLAPIENTRY glTangent3iEXT(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glTangent3iEXT,glTangent3iEXT(_p0,_p1,_p2))
    glCalls().glTangent3iEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangent3iEXT,glTangent3iEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTangent3ivEXT(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glTangent3ivEXT,glTangent3ivEXT(_p0))
    glCalls().glTangent3ivEXT(_p0);
    POST_USER_CALL(glTangent3ivEXT,glTangent3ivEXT(_p0))
}

void GLAPIENTRY glTangent3sEXT(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glTangent3sEXT,glTangent3sEXT(_p0,_p1,_p2))
    glCalls().glTangent3sEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangent3sEXT,glTangent3sEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTangent3svEXT(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glTangent3svEXT,glTangent3svEXT(_p0))
    glCalls().glTangent3svEXT(_p0);
    POST_USER_CALL(glTangent3svEXT,glTangent3svEXT(_p0))
}

void GLAPIENTRY glTangentPointerEXT(GLenum _p0, GLsizei _p1, const GLvoid *_p2)
{
    gli().init();
    PREV_USER_CALL(glTangentPointerEXT,glTangentPointerEXT(_p0,_p1,_p2))
    glCalls().glTangentPointerEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTangentPointerEXT,glTangentPointerEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTbufferMask3DFX(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glTbufferMask3DFX,glTbufferMask3DFX(_p0))
    glCalls().glTbufferMask3DFX(_p0);
    POST_USER_CALL(glTbufferMask3DFX,glTbufferMask3DFX(_p0))
}

void GLAPIENTRY glTessellationFactorAMD(GLfloat _p0)
{
    gli().init();
    PREV_USER_CALL(glTessellationFactorAMD,glTessellationFactorAMD(_p0))
    glCalls().glTessellationFactorAMD(_p0);
    POST_USER_CALL(glTessellationFactorAMD,glTessellationFactorAMD(_p0))
}

void GLAPIENTRY glTessellationModeAMD(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glTessellationModeAMD,glTessellationModeAMD(_p0))
    glCalls().glTessellationModeAMD(_p0);
    POST_USER_CALL(glTessellationModeAMD,glTessellationModeAMD(_p0))
}

GLboolean GLAPIENTRY glTestFenceAPPLE(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glTestFenceAPPLE,glTestFenceAPPLE(_p0))
    _result = glCalls().glTestFenceAPPLE(_p0);
    POST_USER_CALL(glTestFenceAPPLE,glTestFenceAPPLE(_p0))
    return _result;
}

GLboolean GLAPIENTRY glTestFenceNV(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glTestFenceNV,glTestFenceNV(_p0))
    _result = glCalls().glTestFenceNV(_p0);
    POST_USER_CALL(glTestFenceNV,glTestFenceNV(_p0))
    return _result;
}

GLboolean GLAPIENTRY glTestObjectAPPLE(GLenum _p0, GLuint _p1)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glTestObjectAPPLE,glTestObjectAPPLE(_p0,_p1))
    _result = glCalls().glTestObjectAPPLE(_p0,_p1);
    POST_USER_CALL(glTestObjectAPPLE,glTestObjectAPPLE(_p0,_p1))
    return _result;
}

void GLAPIENTRY glTexBuffer(GLenum _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glTexBuffer,glTexBuffer(_p0,_p1,_p2))
    glCalls().glTexBuffer(_p0,_p1,_p2);
    POST_USER_CALL(glTexBuffer,glTexBuffer(_p0,_p1,_p2))
}

void GLAPIENTRY glTexBufferARB(GLenum _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glTexBufferARB,glTexBufferARB(_p0,_p1,_p2))
    glCalls().glTexBufferARB(_p0,_p1,_p2);
    POST_USER_CALL(glTexBufferARB,glTexBufferARB(_p0,_p1,_p2))
}

void GLAPIENTRY glTexBufferEXT(GLenum _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glTexBufferEXT,glTexBufferEXT(_p0,_p1,_p2))
    glCalls().glTexBufferEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTexBufferEXT,glTexBufferEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTexBumpParameterfvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glTexBumpParameterfvATI,glTexBumpParameterfvATI(_p0,_p1))
    glCalls().glTexBumpParameterfvATI(_p0,_p1);
    POST_USER_CALL(glTexBumpParameterfvATI,glTexBumpParameterfvATI(_p0,_p1))
}

void GLAPIENTRY glTexBumpParameterivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glTexBumpParameterivATI,glTexBumpParameterivATI(_p0,_p1))
    glCalls().glTexBumpParameterivATI(_p0,_p1);
    POST_USER_CALL(glTexBumpParameterivATI,glTexBumpParameterivATI(_p0,_p1))
}

void GLAPIENTRY glTexCoord1d(GLdouble s)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1d,glTexCoord1d(s))
    glCalls().glTexCoord1d(s);
    POST_USER_CALL(glTexCoord1d,glTexCoord1d(s))
}

void GLAPIENTRY glTexCoord1dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1dv,glTexCoord1dv(v))
    glCalls().glTexCoord1dv(v);
    POST_USER_CALL(glTexCoord1dv,glTexCoord1dv(v))
}

void GLAPIENTRY glTexCoord1f(GLfloat s)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1f,glTexCoord1f(s))
    glCalls().glTexCoord1f(s);
    POST_USER_CALL(glTexCoord1f,glTexCoord1f(s))
}

void GLAPIENTRY glTexCoord1fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1fv,glTexCoord1fv(v))
    glCalls().glTexCoord1fv(v);
    POST_USER_CALL(glTexCoord1fv,glTexCoord1fv(v))
}

void GLAPIENTRY glTexCoord1hNV(GLhalfNV _p0)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1hNV,glTexCoord1hNV(_p0))
    glCalls().glTexCoord1hNV(_p0);
    POST_USER_CALL(glTexCoord1hNV,glTexCoord1hNV(_p0))
}

void GLAPIENTRY glTexCoord1hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1hvNV,glTexCoord1hvNV(_p0))
    glCalls().glTexCoord1hvNV(_p0);
    POST_USER_CALL(glTexCoord1hvNV,glTexCoord1hvNV(_p0))
}

void GLAPIENTRY glTexCoord1i(GLint s)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1i,glTexCoord1i(s))
    glCalls().glTexCoord1i(s);
    POST_USER_CALL(glTexCoord1i,glTexCoord1i(s))
}

void GLAPIENTRY glTexCoord1iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1iv,glTexCoord1iv(v))
    glCalls().glTexCoord1iv(v);
    POST_USER_CALL(glTexCoord1iv,glTexCoord1iv(v))
}

void GLAPIENTRY glTexCoord1s(GLshort s)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1s,glTexCoord1s(s))
    glCalls().glTexCoord1s(s);
    POST_USER_CALL(glTexCoord1s,glTexCoord1s(s))
}

void GLAPIENTRY glTexCoord1sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord1sv,glTexCoord1sv(v))
    glCalls().glTexCoord1sv(v);
    POST_USER_CALL(glTexCoord1sv,glTexCoord1sv(v))
}

void GLAPIENTRY glTexCoord2d(GLdouble s, GLdouble t)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2d,glTexCoord2d(s,t))
    glCalls().glTexCoord2d(s,t);
    POST_USER_CALL(glTexCoord2d,glTexCoord2d(s,t))
}

void GLAPIENTRY glTexCoord2dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2dv,glTexCoord2dv(v))
    glCalls().glTexCoord2dv(v);
    POST_USER_CALL(glTexCoord2dv,glTexCoord2dv(v))
}

void GLAPIENTRY glTexCoord2f(GLfloat s, GLfloat t)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2f,glTexCoord2f(s,t))
    glCalls().glTexCoord2f(s,t);
    POST_USER_CALL(glTexCoord2f,glTexCoord2f(s,t))
}

void GLAPIENTRY glTexCoord2fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2fv,glTexCoord2fv(v))
    glCalls().glTexCoord2fv(v);
    POST_USER_CALL(glTexCoord2fv,glTexCoord2fv(v))
}

void GLAPIENTRY glTexCoord2hNV(GLhalfNV _p0, GLhalfNV _p1)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2hNV,glTexCoord2hNV(_p0,_p1))
    glCalls().glTexCoord2hNV(_p0,_p1);
    POST_USER_CALL(glTexCoord2hNV,glTexCoord2hNV(_p0,_p1))
}

void GLAPIENTRY glTexCoord2hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2hvNV,glTexCoord2hvNV(_p0))
    glCalls().glTexCoord2hvNV(_p0);
    POST_USER_CALL(glTexCoord2hvNV,glTexCoord2hvNV(_p0))
}

void GLAPIENTRY glTexCoord2i(GLint s, GLint t)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2i,glTexCoord2i(s,t))
    glCalls().glTexCoord2i(s,t);
    POST_USER_CALL(glTexCoord2i,glTexCoord2i(s,t))
}

void GLAPIENTRY glTexCoord2iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2iv,glTexCoord2iv(v))
    glCalls().glTexCoord2iv(v);
    POST_USER_CALL(glTexCoord2iv,glTexCoord2iv(v))
}

void GLAPIENTRY glTexCoord2s(GLshort s, GLshort t)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2s,glTexCoord2s(s,t))
    glCalls().glTexCoord2s(s,t);
    POST_USER_CALL(glTexCoord2s,glTexCoord2s(s,t))
}

void GLAPIENTRY glTexCoord2sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord2sv,glTexCoord2sv(v))
    glCalls().glTexCoord2sv(v);
    POST_USER_CALL(glTexCoord2sv,glTexCoord2sv(v))
}

void GLAPIENTRY glTexCoord3d(GLdouble s, GLdouble t, GLdouble r)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3d,glTexCoord3d(s,t,r))
    glCalls().glTexCoord3d(s,t,r);
    POST_USER_CALL(glTexCoord3d,glTexCoord3d(s,t,r))
}

void GLAPIENTRY glTexCoord3dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3dv,glTexCoord3dv(v))
    glCalls().glTexCoord3dv(v);
    POST_USER_CALL(glTexCoord3dv,glTexCoord3dv(v))
}

void GLAPIENTRY glTexCoord3f(GLfloat s, GLfloat t, GLfloat r)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3f,glTexCoord3f(s,t,r))
    glCalls().glTexCoord3f(s,t,r);
    POST_USER_CALL(glTexCoord3f,glTexCoord3f(s,t,r))
}

void GLAPIENTRY glTexCoord3fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3fv,glTexCoord3fv(v))
    glCalls().glTexCoord3fv(v);
    POST_USER_CALL(glTexCoord3fv,glTexCoord3fv(v))
}

void GLAPIENTRY glTexCoord3hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3hNV,glTexCoord3hNV(_p0,_p1,_p2))
    glCalls().glTexCoord3hNV(_p0,_p1,_p2);
    POST_USER_CALL(glTexCoord3hNV,glTexCoord3hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glTexCoord3hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3hvNV,glTexCoord3hvNV(_p0))
    glCalls().glTexCoord3hvNV(_p0);
    POST_USER_CALL(glTexCoord3hvNV,glTexCoord3hvNV(_p0))
}

void GLAPIENTRY glTexCoord3i(GLint s, GLint t, GLint r)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3i,glTexCoord3i(s,t,r))
    glCalls().glTexCoord3i(s,t,r);
    POST_USER_CALL(glTexCoord3i,glTexCoord3i(s,t,r))
}

void GLAPIENTRY glTexCoord3iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3iv,glTexCoord3iv(v))
    glCalls().glTexCoord3iv(v);
    POST_USER_CALL(glTexCoord3iv,glTexCoord3iv(v))
}

void GLAPIENTRY glTexCoord3s(GLshort s, GLshort t, GLshort r)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3s,glTexCoord3s(s,t,r))
    glCalls().glTexCoord3s(s,t,r);
    POST_USER_CALL(glTexCoord3s,glTexCoord3s(s,t,r))
}

void GLAPIENTRY glTexCoord3sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord3sv,glTexCoord3sv(v))
    glCalls().glTexCoord3sv(v);
    POST_USER_CALL(glTexCoord3sv,glTexCoord3sv(v))
}

void GLAPIENTRY glTexCoord4d(GLdouble s, GLdouble t, GLdouble r, GLdouble q)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4d,glTexCoord4d(s,t,r,q))
    glCalls().glTexCoord4d(s,t,r,q);
    POST_USER_CALL(glTexCoord4d,glTexCoord4d(s,t,r,q))
}

void GLAPIENTRY glTexCoord4dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4dv,glTexCoord4dv(v))
    glCalls().glTexCoord4dv(v);
    POST_USER_CALL(glTexCoord4dv,glTexCoord4dv(v))
}

void GLAPIENTRY glTexCoord4f(GLfloat s, GLfloat t, GLfloat r, GLfloat q)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4f,glTexCoord4f(s,t,r,q))
    glCalls().glTexCoord4f(s,t,r,q);
    POST_USER_CALL(glTexCoord4f,glTexCoord4f(s,t,r,q))
}

void GLAPIENTRY glTexCoord4fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4fv,glTexCoord4fv(v))
    glCalls().glTexCoord4fv(v);
    POST_USER_CALL(glTexCoord4fv,glTexCoord4fv(v))
}

void GLAPIENTRY glTexCoord4hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4hNV,glTexCoord4hNV(_p0,_p1,_p2,_p3))
    glCalls().glTexCoord4hNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTexCoord4hNV,glTexCoord4hNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTexCoord4hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4hvNV,glTexCoord4hvNV(_p0))
    glCalls().glTexCoord4hvNV(_p0);
    POST_USER_CALL(glTexCoord4hvNV,glTexCoord4hvNV(_p0))
}

void GLAPIENTRY glTexCoord4i(GLint s, GLint t, GLint r, GLint q)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4i,glTexCoord4i(s,t,r,q))
    glCalls().glTexCoord4i(s,t,r,q);
    POST_USER_CALL(glTexCoord4i,glTexCoord4i(s,t,r,q))
}

void GLAPIENTRY glTexCoord4iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4iv,glTexCoord4iv(v))
    glCalls().glTexCoord4iv(v);
    POST_USER_CALL(glTexCoord4iv,glTexCoord4iv(v))
}

void GLAPIENTRY glTexCoord4s(GLshort s, GLshort t, GLshort r, GLshort q)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4s,glTexCoord4s(s,t,r,q))
    glCalls().glTexCoord4s(s,t,r,q);
    POST_USER_CALL(glTexCoord4s,glTexCoord4s(s,t,r,q))
}

void GLAPIENTRY glTexCoord4sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glTexCoord4sv,glTexCoord4sv(v))
    glCalls().glTexCoord4sv(v);
    POST_USER_CALL(glTexCoord4sv,glTexCoord4sv(v))
}

void GLAPIENTRY glTexCoordPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glTexCoordPointer,glTexCoordPointer(size,type,stride,ptr))
    glCalls().glTexCoordPointer(size,type,stride,ptr);
    POST_USER_CALL(glTexCoordPointer,glTexCoordPointer(size,type,stride,ptr))
}

void GLAPIENTRY glTexCoordPointerEXT(GLint _p0, GLenum _p1, GLsizei _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glTexCoordPointerEXT,glTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glTexCoordPointerEXT,glTexCoordPointerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glTexCoordPointervINTEL(GLint _p0, GLenum _p1, const GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glTexCoordPointervINTEL,glTexCoordPointervINTEL(_p0,_p1,_p2))
    glCalls().glTexCoordPointervINTEL(_p0,_p1,_p2);
    POST_USER_CALL(glTexCoordPointervINTEL,glTexCoordPointervINTEL(_p0,_p1,_p2))
}

void GLAPIENTRY glTexEnvf(GLenum target, GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glTexEnvf,glTexEnvf(target,pname,param))
    glCalls().glTexEnvf(target,pname,param);
    POST_USER_CALL(glTexEnvf,glTexEnvf(target,pname,param))
}

void GLAPIENTRY glTexEnvfv(GLenum target, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glTexEnvfv,glTexEnvfv(target,pname,params))
    glCalls().glTexEnvfv(target,pname,params);
    POST_USER_CALL(glTexEnvfv,glTexEnvfv(target,pname,params))
}

void GLAPIENTRY glTexEnvi(GLenum target, GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glTexEnvi,glTexEnvi(target,pname,param))
    glCalls().glTexEnvi(target,pname,param);
    POST_USER_CALL(glTexEnvi,glTexEnvi(target,pname,param))
}

void GLAPIENTRY glTexEnviv(GLenum target, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glTexEnviv,glTexEnviv(target,pname,params))
    glCalls().glTexEnviv(target,pname,params);
    POST_USER_CALL(glTexEnviv,glTexEnviv(target,pname,params))
}

void GLAPIENTRY glTexFilterFuncSGIS(GLenum _p0, GLenum _p1, GLsizei _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glTexFilterFuncSGIS,glTexFilterFuncSGIS(_p0,_p1,_p2,_p3))
    glCalls().glTexFilterFuncSGIS(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTexFilterFuncSGIS,glTexFilterFuncSGIS(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTexGend(GLenum coord, GLenum pname, GLdouble param)
{
    gli().init();
    PREV_USER_CALL(glTexGend,glTexGend(coord,pname,param))
    glCalls().glTexGend(coord,pname,param);
    POST_USER_CALL(glTexGend,glTexGend(coord,pname,param))
}

void GLAPIENTRY glTexGendv(GLenum coord, GLenum pname, const GLdouble *params)
{
    gli().init();
    PREV_USER_CALL(glTexGendv,glTexGendv(coord,pname,params))
    glCalls().glTexGendv(coord,pname,params);
    POST_USER_CALL(glTexGendv,glTexGendv(coord,pname,params))
}

void GLAPIENTRY glTexGenf(GLenum coord, GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glTexGenf,glTexGenf(coord,pname,param))
    glCalls().glTexGenf(coord,pname,param);
    POST_USER_CALL(glTexGenf,glTexGenf(coord,pname,param))
}

void GLAPIENTRY glTexGenfv(GLenum coord, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glTexGenfv,glTexGenfv(coord,pname,params))
    glCalls().glTexGenfv(coord,pname,params);
    POST_USER_CALL(glTexGenfv,glTexGenfv(coord,pname,params))
}

void GLAPIENTRY glTexGeni(GLenum coord, GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glTexGeni,glTexGeni(coord,pname,param))
    glCalls().glTexGeni(coord,pname,param);
    POST_USER_CALL(glTexGeni,glTexGeni(coord,pname,param))
}

void GLAPIENTRY glTexGeniv(GLenum coord, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glTexGeniv,glTexGeniv(coord,pname,params))
    glCalls().glTexGeniv(coord,pname,params);
    POST_USER_CALL(glTexGeniv,glTexGeniv(coord,pname,params))
}

void GLAPIENTRY glTexImage1D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexImage1D,glTexImage1D(target,level,internalFormat,width,border,format,type,pixels))
    glCalls().glTexImage1D(target,level,internalFormat,width,border,format,type,pixels);
    POST_USER_CALL(glTexImage1D,glTexImage1D(target,level,internalFormat,width,border,format,type,pixels))
}

void GLAPIENTRY glTexImage2D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexImage2D,glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels))
    glCalls().glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels);
    POST_USER_CALL(glTexImage2D,glTexImage2D(target,level,internalFormat,width,height,border,format,type,pixels))
}

void GLAPIENTRY glTexImage3D(GLenum target, GLint level, GLint internalFormat, GLsizei width, GLsizei height, GLsizei depth, GLint border, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexImage3D,glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,pixels))
    glCalls().glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,pixels);
    POST_USER_CALL(glTexImage3D,glTexImage3D(target,level,internalFormat,width,height,depth,border,format,type,pixels))
}

void GLAPIENTRY glTexImage3DEXT(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLenum _p7, GLenum _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glTexImage3DEXT,glTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glTexImage3DEXT,glTexImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glTexImage4DSGIS(GLenum _p0, GLint _p1, GLenum _p2, GLsizei _p3, GLsizei _p4, GLsizei _p5, GLsizei _p6, GLint _p7, GLenum _p8, GLenum _p9, const GLvoid *_p10)
{
    gli().init();
    PREV_USER_CALL(glTexImage4DSGIS,glTexImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glTexImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glTexImage4DSGIS,glTexImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glTexParameterIiv(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glTexParameterIiv,glTexParameterIiv(_p0,_p1,_p2))
    glCalls().glTexParameterIiv(_p0,_p1,_p2);
    POST_USER_CALL(glTexParameterIiv,glTexParameterIiv(_p0,_p1,_p2))
}

void GLAPIENTRY glTexParameterIivEXT(GLenum _p0, GLenum _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glTexParameterIivEXT,glTexParameterIivEXT(_p0,_p1,_p2))
    glCalls().glTexParameterIivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTexParameterIivEXT,glTexParameterIivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTexParameterIuiv(GLenum _p0, GLenum _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glTexParameterIuiv,glTexParameterIuiv(_p0,_p1,_p2))
    glCalls().glTexParameterIuiv(_p0,_p1,_p2);
    POST_USER_CALL(glTexParameterIuiv,glTexParameterIuiv(_p0,_p1,_p2))
}

void GLAPIENTRY glTexParameterIuivEXT(GLenum _p0, GLenum _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glTexParameterIuivEXT,glTexParameterIuivEXT(_p0,_p1,_p2))
    glCalls().glTexParameterIuivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTexParameterIuivEXT,glTexParameterIuivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTexParameterf(GLenum target, GLenum pname, GLfloat param)
{
    gli().init();
    PREV_USER_CALL(glTexParameterf,glTexParameterf(target,pname,param))
    glCalls().glTexParameterf(target,pname,param);
    POST_USER_CALL(glTexParameterf,glTexParameterf(target,pname,param))
}

void GLAPIENTRY glTexParameterfv(GLenum target, GLenum pname, const GLfloat *params)
{
    gli().init();
    PREV_USER_CALL(glTexParameterfv,glTexParameterfv(target,pname,params))
    glCalls().glTexParameterfv(target,pname,params);
    POST_USER_CALL(glTexParameterfv,glTexParameterfv(target,pname,params))
}

void GLAPIENTRY glTexParameteri(GLenum target, GLenum pname, GLint param)
{
    gli().init();
    PREV_USER_CALL(glTexParameteri,glTexParameteri(target,pname,param))
    glCalls().glTexParameteri(target,pname,param);
    POST_USER_CALL(glTexParameteri,glTexParameteri(target,pname,param))
}

void GLAPIENTRY glTexParameteriv(GLenum target, GLenum pname, const GLint *params)
{
    gli().init();
    PREV_USER_CALL(glTexParameteriv,glTexParameteriv(target,pname,params))
    glCalls().glTexParameteriv(target,pname,params);
    POST_USER_CALL(glTexParameteriv,glTexParameteriv(target,pname,params))
}

void GLAPIENTRY glTexRenderbufferNV(GLenum _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glTexRenderbufferNV,glTexRenderbufferNV(_p0,_p1))
    glCalls().glTexRenderbufferNV(_p0,_p1);
    POST_USER_CALL(glTexRenderbufferNV,glTexRenderbufferNV(_p0,_p1))
}

void GLAPIENTRY glTexSubImage1D(GLenum target, GLint level, GLint xoffset, GLsizei width, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage1D,glTexSubImage1D(target,level,xoffset,width,format,type,pixels))
    glCalls().glTexSubImage1D(target,level,xoffset,width,format,type,pixels);
    POST_USER_CALL(glTexSubImage1D,glTexSubImage1D(target,level,xoffset,width,format,type,pixels))
}

void GLAPIENTRY glTexSubImage1DEXT(GLenum _p0, GLint _p1, GLint _p2, GLsizei _p3, GLenum _p4, GLenum _p5, const GLvoid *_p6)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage1DEXT,glTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glTexSubImage1DEXT,glTexSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glTexSubImage2D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLsizei width, GLsizei height, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage2D,glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels))
    glCalls().glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels);
    POST_USER_CALL(glTexSubImage2D,glTexSubImage2D(target,level,xoffset,yoffset,width,height,format,type,pixels))
}

void GLAPIENTRY glTexSubImage2DEXT(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLsizei _p4, GLsizei _p5, GLenum _p6, GLenum _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage2DEXT,glTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glTexSubImage2DEXT,glTexSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glTexSubImage3D(GLenum target, GLint level, GLint xoffset, GLint yoffset, GLint zoffset, GLsizei width, GLsizei height, GLsizei depth, GLenum format, GLenum type, const GLvoid *pixels)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage3D,glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels))
    glCalls().glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels);
    POST_USER_CALL(glTexSubImage3D,glTexSubImage3D(target,level,xoffset,yoffset,zoffset,width,height,depth,format,type,pixels))
}

void GLAPIENTRY glTexSubImage3DEXT(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLsizei _p7, GLenum _p8, GLenum _p9, const GLvoid *_p10)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage3DEXT,glTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glTexSubImage3DEXT,glTexSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glTexSubImage4DSGIS(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLsizei _p8, GLsizei _p9, GLenum _p10, GLenum _p11, const GLvoid *_p12)
{
    gli().init();
    PREV_USER_CALL(glTexSubImage4DSGIS,glTexSubImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
    glCalls().glTexSubImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12);
    POST_USER_CALL(glTexSubImage4DSGIS,glTexSubImage4DSGIS(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11,_p12))
}

void GLAPIENTRY glTextureBufferEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glTextureBufferEXT,glTextureBufferEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureBufferEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureBufferEXT,glTextureBufferEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureColorMaskSGIS(GLboolean _p0, GLboolean _p1, GLboolean _p2, GLboolean _p3)
{
    gli().init();
    PREV_USER_CALL(glTextureColorMaskSGIS,glTextureColorMaskSGIS(_p0,_p1,_p2,_p3))
    glCalls().glTextureColorMaskSGIS(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureColorMaskSGIS,glTextureColorMaskSGIS(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLint _p5, GLenum _p6, GLenum _p7, const GLvoid *_p8)
{
    gli().init();
    PREV_USER_CALL(glTextureImage1DEXT,glTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
    glCalls().glTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8);
    POST_USER_CALL(glTextureImage1DEXT,glTextureImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8))
}

void GLAPIENTRY glTextureImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLint _p6, GLenum _p7, GLenum _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glTextureImage2DEXT,glTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glTextureImage2DEXT,glTextureImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glTextureImage3DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLenum _p3, GLsizei _p4, GLsizei _p5, GLsizei _p6, GLint _p7, GLenum _p8, GLenum _p9, const GLvoid *_p10)
{
    gli().init();
    PREV_USER_CALL(glTextureImage3DEXT,glTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
    glCalls().glTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10);
    POST_USER_CALL(glTextureImage3DEXT,glTextureImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10))
}

void GLAPIENTRY glTextureLightEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glTextureLightEXT,glTextureLightEXT(_p0))
    glCalls().glTextureLightEXT(_p0);
    POST_USER_CALL(glTextureLightEXT,glTextureLightEXT(_p0))
}

void GLAPIENTRY glTextureMaterialEXT(GLenum _p0, GLenum _p1)
{
    gli().init();
    PREV_USER_CALL(glTextureMaterialEXT,glTextureMaterialEXT(_p0,_p1))
    glCalls().glTextureMaterialEXT(_p0,_p1);
    POST_USER_CALL(glTextureMaterialEXT,glTextureMaterialEXT(_p0,_p1))
}

void GLAPIENTRY glTextureNormalEXT(GLenum _p0)
{
    gli().init();
    PREV_USER_CALL(glTextureNormalEXT,glTextureNormalEXT(_p0))
    glCalls().glTextureNormalEXT(_p0);
    POST_USER_CALL(glTextureNormalEXT,glTextureNormalEXT(_p0))
}

void GLAPIENTRY glTextureParameterIivEXT(GLuint _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameterIivEXT,glTextureParameterIivEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameterIivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameterIivEXT,glTextureParameterIivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureParameterIuivEXT(GLuint _p0, GLenum _p1, GLenum _p2, const GLuint *_p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameterIuivEXT,glTextureParameterIuivEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameterIuivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameterIuivEXT,glTextureParameterIuivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureParameterfEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameterfEXT,glTextureParameterfEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameterfEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameterfEXT,glTextureParameterfEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureParameterfvEXT(GLuint _p0, GLenum _p1, GLenum _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameterfvEXT,glTextureParameterfvEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameterfvEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameterfvEXT,glTextureParameterfvEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureParameteriEXT(GLuint _p0, GLenum _p1, GLenum _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameteriEXT,glTextureParameteriEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameteriEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameteriEXT,glTextureParameteriEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureParameterivEXT(GLuint _p0, GLenum _p1, GLenum _p2, const GLint *_p3)
{
    gli().init();
    PREV_USER_CALL(glTextureParameterivEXT,glTextureParameterivEXT(_p0,_p1,_p2,_p3))
    glCalls().glTextureParameterivEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTextureParameterivEXT,glTextureParameterivEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTextureRenderbufferEXT(GLuint _p0, GLenum _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glTextureRenderbufferEXT,glTextureRenderbufferEXT(_p0,_p1,_p2))
    glCalls().glTextureRenderbufferEXT(_p0,_p1,_p2);
    POST_USER_CALL(glTextureRenderbufferEXT,glTextureRenderbufferEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glTextureSubImage1DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLsizei _p4, GLenum _p5, GLenum _p6, const GLvoid *_p7)
{
    gli().init();
    PREV_USER_CALL(glTextureSubImage1DEXT,glTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    glCalls().glTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(glTextureSubImage1DEXT,glTextureSubImage1DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
}

void GLAPIENTRY glTextureSubImage2DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLsizei _p5, GLsizei _p6, GLenum _p7, GLenum _p8, const GLvoid *_p9)
{
    gli().init();
    PREV_USER_CALL(glTextureSubImage2DEXT,glTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
    glCalls().glTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9);
    POST_USER_CALL(glTextureSubImage2DEXT,glTextureSubImage2DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9))
}

void GLAPIENTRY glTextureSubImage3DEXT(GLuint _p0, GLenum _p1, GLint _p2, GLint _p3, GLint _p4, GLint _p5, GLsizei _p6, GLsizei _p7, GLsizei _p8, GLenum _p9, GLenum _p10, const GLvoid *_p11)
{
    gli().init();
    PREV_USER_CALL(glTextureSubImage3DEXT,glTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
    glCalls().glTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11);
    POST_USER_CALL(glTextureSubImage3DEXT,glTextureSubImage3DEXT(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7,_p8,_p9,_p10,_p11))
}

void GLAPIENTRY glTrackMatrixNV(GLenum _p0, GLuint _p1, GLenum _p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glTrackMatrixNV,glTrackMatrixNV(_p0,_p1,_p2,_p3))
    glCalls().glTrackMatrixNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTrackMatrixNV,glTrackMatrixNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTransformFeedbackAttribsNV(GLuint _p0, const GLint *_p1, GLenum _p2)
{
    gli().init();
    PREV_USER_CALL(glTransformFeedbackAttribsNV,glTransformFeedbackAttribsNV(_p0,_p1,_p2))
    glCalls().glTransformFeedbackAttribsNV(_p0,_p1,_p2);
    POST_USER_CALL(glTransformFeedbackAttribsNV,glTransformFeedbackAttribsNV(_p0,_p1,_p2))
}

void GLAPIENTRY glTransformFeedbackVaryings(GLuint _p0, GLsizei _p1, const GLchar **_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glTransformFeedbackVaryings,glTransformFeedbackVaryings(_p0,_p1,_p2,_p3))
    glCalls().glTransformFeedbackVaryings(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTransformFeedbackVaryings,glTransformFeedbackVaryings(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTransformFeedbackVaryingsEXT(GLuint _p0, GLsizei _p1, const GLchar **_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glTransformFeedbackVaryingsEXT,glTransformFeedbackVaryingsEXT(_p0,_p1,_p2,_p3))
    glCalls().glTransformFeedbackVaryingsEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTransformFeedbackVaryingsEXT,glTransformFeedbackVaryingsEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTransformFeedbackVaryingsNV(GLuint _p0, GLsizei _p1, const GLint *_p2, GLenum _p3)
{
    gli().init();
    PREV_USER_CALL(glTransformFeedbackVaryingsNV,glTransformFeedbackVaryingsNV(_p0,_p1,_p2,_p3))
    glCalls().glTransformFeedbackVaryingsNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glTransformFeedbackVaryingsNV,glTransformFeedbackVaryingsNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glTranslated(GLdouble x, GLdouble y, GLdouble z)
{
    gli().init();
    PREV_USER_CALL(glTranslated,glTranslated(x,y,z))
    glCalls().glTranslated(x,y,z);
    POST_USER_CALL(glTranslated,glTranslated(x,y,z))
}

void GLAPIENTRY glTranslatef(GLfloat x, GLfloat y, GLfloat z)
{
    gli().init();
    PREV_USER_CALL(glTranslatef,glTranslatef(x,y,z))
    glCalls().glTranslatef(x,y,z);
    POST_USER_CALL(glTranslatef,glTranslatef(x,y,z))
}

void GLAPIENTRY glUniform1f(GLint _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1f,glUniform1f(_p0,_p1))
    glCalls().glUniform1f(_p0,_p1);
    POST_USER_CALL(glUniform1f,glUniform1f(_p0,_p1))
}

void GLAPIENTRY glUniform1fARB(GLint _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1fARB,glUniform1fARB(_p0,_p1))
    glCalls().glUniform1fARB(_p0,_p1);
    POST_USER_CALL(glUniform1fARB,glUniform1fARB(_p0,_p1))
}

void GLAPIENTRY glUniform1fv(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1fv,glUniform1fv(_p0,_p1,_p2))
    glCalls().glUniform1fv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1fv,glUniform1fv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform1fvARB(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1fvARB,glUniform1fvARB(_p0,_p1,_p2))
    glCalls().glUniform1fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1fvARB,glUniform1fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform1i(GLint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1i,glUniform1i(_p0,_p1))
    glCalls().glUniform1i(_p0,_p1);
    POST_USER_CALL(glUniform1i,glUniform1i(_p0,_p1))
}

void GLAPIENTRY glUniform1iARB(GLint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1iARB,glUniform1iARB(_p0,_p1))
    glCalls().glUniform1iARB(_p0,_p1);
    POST_USER_CALL(glUniform1iARB,glUniform1iARB(_p0,_p1))
}

void GLAPIENTRY glUniform1iv(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1iv,glUniform1iv(_p0,_p1,_p2))
    glCalls().glUniform1iv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1iv,glUniform1iv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform1ivARB(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1ivARB,glUniform1ivARB(_p0,_p1,_p2))
    glCalls().glUniform1ivARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1ivARB,glUniform1ivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform1ui(GLint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1ui,glUniform1ui(_p0,_p1))
    glCalls().glUniform1ui(_p0,_p1);
    POST_USER_CALL(glUniform1ui,glUniform1ui(_p0,_p1))
}

void GLAPIENTRY glUniform1uiEXT(GLint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glUniform1uiEXT,glUniform1uiEXT(_p0,_p1))
    glCalls().glUniform1uiEXT(_p0,_p1);
    POST_USER_CALL(glUniform1uiEXT,glUniform1uiEXT(_p0,_p1))
}

void GLAPIENTRY glUniform1uiv(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1uiv,glUniform1uiv(_p0,_p1,_p2))
    glCalls().glUniform1uiv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1uiv,glUniform1uiv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform1uivEXT(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform1uivEXT,glUniform1uivEXT(_p0,_p1,_p2))
    glCalls().glUniform1uivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniform1uivEXT,glUniform1uivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2f(GLint _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2f,glUniform2f(_p0,_p1,_p2))
    glCalls().glUniform2f(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2f,glUniform2f(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2fARB(GLint _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2fARB,glUniform2fARB(_p0,_p1,_p2))
    glCalls().glUniform2fARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2fARB,glUniform2fARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2fv(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2fv,glUniform2fv(_p0,_p1,_p2))
    glCalls().glUniform2fv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2fv,glUniform2fv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2fvARB(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2fvARB,glUniform2fvARB(_p0,_p1,_p2))
    glCalls().glUniform2fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2fvARB,glUniform2fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2i(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2i,glUniform2i(_p0,_p1,_p2))
    glCalls().glUniform2i(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2i,glUniform2i(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2iARB(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2iARB,glUniform2iARB(_p0,_p1,_p2))
    glCalls().glUniform2iARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2iARB,glUniform2iARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2iv(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2iv,glUniform2iv(_p0,_p1,_p2))
    glCalls().glUniform2iv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2iv,glUniform2iv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2ivARB(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2ivARB,glUniform2ivARB(_p0,_p1,_p2))
    glCalls().glUniform2ivARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2ivARB,glUniform2ivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2ui(GLint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2ui,glUniform2ui(_p0,_p1,_p2))
    glCalls().glUniform2ui(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2ui,glUniform2ui(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2uiEXT(GLint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2uiEXT,glUniform2uiEXT(_p0,_p1,_p2))
    glCalls().glUniform2uiEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2uiEXT,glUniform2uiEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2uiv(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2uiv,glUniform2uiv(_p0,_p1,_p2))
    glCalls().glUniform2uiv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2uiv,glUniform2uiv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform2uivEXT(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform2uivEXT,glUniform2uivEXT(_p0,_p1,_p2))
    glCalls().glUniform2uivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniform2uivEXT,glUniform2uivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3f(GLint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3f,glUniform3f(_p0,_p1,_p2,_p3))
    glCalls().glUniform3f(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3f,glUniform3f(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3fARB(GLint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3fARB,glUniform3fARB(_p0,_p1,_p2,_p3))
    glCalls().glUniform3fARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3fARB,glUniform3fARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3fv(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3fv,glUniform3fv(_p0,_p1,_p2))
    glCalls().glUniform3fv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3fv,glUniform3fv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3fvARB(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3fvARB,glUniform3fvARB(_p0,_p1,_p2))
    glCalls().glUniform3fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3fvARB,glUniform3fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3i(GLint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3i,glUniform3i(_p0,_p1,_p2,_p3))
    glCalls().glUniform3i(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3i,glUniform3i(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3iARB(GLint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3iARB,glUniform3iARB(_p0,_p1,_p2,_p3))
    glCalls().glUniform3iARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3iARB,glUniform3iARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3iv(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3iv,glUniform3iv(_p0,_p1,_p2))
    glCalls().glUniform3iv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3iv,glUniform3iv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3ivARB(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3ivARB,glUniform3ivARB(_p0,_p1,_p2))
    glCalls().glUniform3ivARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3ivARB,glUniform3ivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3ui(GLint _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3ui,glUniform3ui(_p0,_p1,_p2,_p3))
    glCalls().glUniform3ui(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3ui,glUniform3ui(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3uiEXT(GLint _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glUniform3uiEXT,glUniform3uiEXT(_p0,_p1,_p2,_p3))
    glCalls().glUniform3uiEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniform3uiEXT,glUniform3uiEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniform3uiv(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3uiv,glUniform3uiv(_p0,_p1,_p2))
    glCalls().glUniform3uiv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3uiv,glUniform3uiv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform3uivEXT(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform3uivEXT,glUniform3uivEXT(_p0,_p1,_p2))
    glCalls().glUniform3uivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniform3uivEXT,glUniform3uivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4f(GLint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4f,glUniform4f(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4f(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4f,glUniform4f(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4fARB(GLint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4fARB,glUniform4fARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4fARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4fARB,glUniform4fARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4fv(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4fv,glUniform4fv(_p0,_p1,_p2))
    glCalls().glUniform4fv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4fv,glUniform4fv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4fvARB(GLint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4fvARB,glUniform4fvARB(_p0,_p1,_p2))
    glCalls().glUniform4fvARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4fvARB,glUniform4fvARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4i(GLint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4i,glUniform4i(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4i(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4i,glUniform4i(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4iARB(GLint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4iARB,glUniform4iARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4iARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4iARB,glUniform4iARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4iv(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4iv,glUniform4iv(_p0,_p1,_p2))
    glCalls().glUniform4iv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4iv,glUniform4iv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4ivARB(GLint _p0, GLsizei _p1, const GLint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4ivARB,glUniform4ivARB(_p0,_p1,_p2))
    glCalls().glUniform4ivARB(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4ivARB,glUniform4ivARB(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4ui(GLint _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4ui,glUniform4ui(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4ui(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4ui,glUniform4ui(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4uiEXT(GLint _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glUniform4uiEXT,glUniform4uiEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUniform4uiEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUniform4uiEXT,glUniform4uiEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUniform4uiv(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4uiv,glUniform4uiv(_p0,_p1,_p2))
    glCalls().glUniform4uiv(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4uiv,glUniform4uiv(_p0,_p1,_p2))
}

void GLAPIENTRY glUniform4uivEXT(GLint _p0, GLsizei _p1, const GLuint *_p2)
{
    gli().init();
    PREV_USER_CALL(glUniform4uivEXT,glUniform4uivEXT(_p0,_p1,_p2))
    glCalls().glUniform4uivEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniform4uivEXT,glUniform4uivEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniformBlockBinding(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniformBlockBinding,glUniformBlockBinding(_p0,_p1,_p2))
    glCalls().glUniformBlockBinding(_p0,_p1,_p2);
    POST_USER_CALL(glUniformBlockBinding,glUniformBlockBinding(_p0,_p1,_p2))
}

void GLAPIENTRY glUniformBufferEXT(GLuint _p0, GLint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glUniformBufferEXT,glUniformBufferEXT(_p0,_p1,_p2))
    glCalls().glUniformBufferEXT(_p0,_p1,_p2);
    POST_USER_CALL(glUniformBufferEXT,glUniformBufferEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glUniformMatrix2fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix2fv,glUniformMatrix2fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix2fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix2fv,glUniformMatrix2fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix2fvARB(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix2fvARB,glUniformMatrix2fvARB(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix2fvARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix2fvARB,glUniformMatrix2fvARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix2x3fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix2x3fv,glUniformMatrix2x3fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix2x3fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix2x3fv,glUniformMatrix2x3fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix2x4fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix2x4fv,glUniformMatrix2x4fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix2x4fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix2x4fv,glUniformMatrix2x4fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix3fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix3fv,glUniformMatrix3fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix3fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix3fv,glUniformMatrix3fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix3fvARB(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix3fvARB,glUniformMatrix3fvARB(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix3fvARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix3fvARB,glUniformMatrix3fvARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix3x2fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix3x2fv,glUniformMatrix3x2fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix3x2fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix3x2fv,glUniformMatrix3x2fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix3x4fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix3x4fv,glUniformMatrix3x4fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix3x4fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix3x4fv,glUniformMatrix3x4fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix4fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix4fv,glUniformMatrix4fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix4fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix4fv,glUniformMatrix4fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix4fvARB(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix4fvARB,glUniformMatrix4fvARB(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix4fvARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix4fvARB,glUniformMatrix4fvARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix4x2fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix4x2fv,glUniformMatrix4x2fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix4x2fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix4x2fv,glUniformMatrix4x2fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUniformMatrix4x3fv(GLint _p0, GLsizei _p1, GLboolean _p2, const GLfloat *_p3)
{
    gli().init();
    PREV_USER_CALL(glUniformMatrix4x3fv,glUniformMatrix4x3fv(_p0,_p1,_p2,_p3))
    glCalls().glUniformMatrix4x3fv(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glUniformMatrix4x3fv,glUniformMatrix4x3fv(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glUnlockArraysEXT()
{
    gli().init();
    PREV_USER_CALL(glUnlockArraysEXT,glUnlockArraysEXT())
    glCalls().glUnlockArraysEXT();
    POST_USER_CALL(glUnlockArraysEXT,glUnlockArraysEXT())
}

GLboolean GLAPIENTRY glUnmapBuffer(GLenum _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glUnmapBuffer,glUnmapBuffer(_p0))
    _result = glCalls().glUnmapBuffer(_p0);
    POST_USER_CALL(glUnmapBuffer,glUnmapBuffer(_p0))
    return _result;
}

GLboolean GLAPIENTRY glUnmapBufferARB(GLenum _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glUnmapBufferARB,glUnmapBufferARB(_p0))
    _result = glCalls().glUnmapBufferARB(_p0);
    POST_USER_CALL(glUnmapBufferARB,glUnmapBufferARB(_p0))
    return _result;
}

GLboolean GLAPIENTRY glUnmapNamedBufferEXT(GLuint _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(glUnmapNamedBufferEXT,glUnmapNamedBufferEXT(_p0))
    _result = glCalls().glUnmapNamedBufferEXT(_p0);
    POST_USER_CALL(glUnmapNamedBufferEXT,glUnmapNamedBufferEXT(_p0))
    return _result;
}

void GLAPIENTRY glUnmapObjectBufferATI(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glUnmapObjectBufferATI,glUnmapObjectBufferATI(_p0))
    glCalls().glUnmapObjectBufferATI(_p0);
    POST_USER_CALL(glUnmapObjectBufferATI,glUnmapObjectBufferATI(_p0))
}

void GLAPIENTRY glUpdateObjectBufferATI(GLuint _p0, GLuint _p1, GLsizei _p2, const GLvoid *_p3, GLenum _p4)
{
    gli().init();
    PREV_USER_CALL(glUpdateObjectBufferATI,glUpdateObjectBufferATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glUpdateObjectBufferATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glUpdateObjectBufferATI,glUpdateObjectBufferATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glUseProgram(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glUseProgram,glUseProgram(_p0))
    glCalls().glUseProgram(_p0);
    POST_USER_CALL(glUseProgram,glUseProgram(_p0))
}

void GLAPIENTRY glUseProgramObjectARB(GLhandleARB _p0)
{
    gli().init();
    PREV_USER_CALL(glUseProgramObjectARB,glUseProgramObjectARB(_p0))
    glCalls().glUseProgramObjectARB(_p0);
    POST_USER_CALL(glUseProgramObjectARB,glUseProgramObjectARB(_p0))
}

void GLAPIENTRY glValidateProgram(GLuint _p0)
{
    gli().init();
    PREV_USER_CALL(glValidateProgram,glValidateProgram(_p0))
    glCalls().glValidateProgram(_p0);
    POST_USER_CALL(glValidateProgram,glValidateProgram(_p0))
}

void GLAPIENTRY glValidateProgramARB(GLhandleARB _p0)
{
    gli().init();
    PREV_USER_CALL(glValidateProgramARB,glValidateProgramARB(_p0))
    glCalls().glValidateProgramARB(_p0);
    POST_USER_CALL(glValidateProgramARB,glValidateProgramARB(_p0))
}

void GLAPIENTRY glVariantArrayObjectATI(GLuint _p0, GLenum _p1, GLsizei _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glVariantArrayObjectATI,glVariantArrayObjectATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVariantArrayObjectATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVariantArrayObjectATI,glVariantArrayObjectATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVariantPointerEXT(GLuint _p0, GLenum _p1, GLuint _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glVariantPointerEXT,glVariantPointerEXT(_p0,_p1,_p2,_p3))
    glCalls().glVariantPointerEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVariantPointerEXT,glVariantPointerEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVariantbvEXT(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantbvEXT,glVariantbvEXT(_p0,_p1))
    glCalls().glVariantbvEXT(_p0,_p1);
    POST_USER_CALL(glVariantbvEXT,glVariantbvEXT(_p0,_p1))
}

void GLAPIENTRY glVariantdvEXT(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantdvEXT,glVariantdvEXT(_p0,_p1))
    glCalls().glVariantdvEXT(_p0,_p1);
    POST_USER_CALL(glVariantdvEXT,glVariantdvEXT(_p0,_p1))
}

void GLAPIENTRY glVariantfvEXT(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantfvEXT,glVariantfvEXT(_p0,_p1))
    glCalls().glVariantfvEXT(_p0,_p1);
    POST_USER_CALL(glVariantfvEXT,glVariantfvEXT(_p0,_p1))
}

void GLAPIENTRY glVariantivEXT(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantivEXT,glVariantivEXT(_p0,_p1))
    glCalls().glVariantivEXT(_p0,_p1);
    POST_USER_CALL(glVariantivEXT,glVariantivEXT(_p0,_p1))
}

void GLAPIENTRY glVariantsvEXT(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantsvEXT,glVariantsvEXT(_p0,_p1))
    glCalls().glVariantsvEXT(_p0,_p1);
    POST_USER_CALL(glVariantsvEXT,glVariantsvEXT(_p0,_p1))
}

void GLAPIENTRY glVariantubvEXT(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantubvEXT,glVariantubvEXT(_p0,_p1))
    glCalls().glVariantubvEXT(_p0,_p1);
    POST_USER_CALL(glVariantubvEXT,glVariantubvEXT(_p0,_p1))
}

void GLAPIENTRY glVariantuivEXT(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantuivEXT,glVariantuivEXT(_p0,_p1))
    glCalls().glVariantuivEXT(_p0,_p1);
    POST_USER_CALL(glVariantuivEXT,glVariantuivEXT(_p0,_p1))
}

void GLAPIENTRY glVariantusvEXT(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVariantusvEXT,glVariantusvEXT(_p0,_p1))
    glCalls().glVariantusvEXT(_p0,_p1);
    POST_USER_CALL(glVariantusvEXT,glVariantusvEXT(_p0,_p1))
}

void GLAPIENTRY glVertex2d(GLdouble x, GLdouble y)
{
    gli().init();
    PREV_USER_CALL(glVertex2d,glVertex2d(x,y))
    glCalls().glVertex2d(x,y);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2d,glVertex2d(x,y))
}

void GLAPIENTRY glVertex2dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glVertex2dv,glVertex2dv(v))
    glCalls().glVertex2dv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2dv,glVertex2dv(v))
}

void GLAPIENTRY glVertex2f(GLfloat x, GLfloat y)
{
    gli().init();
    PREV_USER_CALL(glVertex2f,glVertex2f(x,y))
    glCalls().glVertex2f(x,y);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2f,glVertex2f(x,y))
}

void GLAPIENTRY glVertex2fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glVertex2fv,glVertex2fv(v))
    glCalls().glVertex2fv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2fv,glVertex2fv(v))
}

void GLAPIENTRY glVertex2hNV(GLhalfNV _p0, GLhalfNV _p1)
{
    gli().init();
    PREV_USER_CALL(glVertex2hNV,glVertex2hNV(_p0,_p1))
    glCalls().glVertex2hNV(_p0,_p1);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2hNV,glVertex2hNV(_p0,_p1))
}

void GLAPIENTRY glVertex2hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glVertex2hvNV,glVertex2hvNV(_p0))
    glCalls().glVertex2hvNV(_p0);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2hvNV,glVertex2hvNV(_p0))
}

void GLAPIENTRY glVertex2i(GLint x, GLint y)
{
    gli().init();
    PREV_USER_CALL(glVertex2i,glVertex2i(x,y))
    glCalls().glVertex2i(x,y);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2i,glVertex2i(x,y))
}

void GLAPIENTRY glVertex2iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glVertex2iv,glVertex2iv(v))
    glCalls().glVertex2iv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2iv,glVertex2iv(v))
}

void GLAPIENTRY glVertex2s(GLshort x, GLshort y)
{
    gli().init();
    PREV_USER_CALL(glVertex2s,glVertex2s(x,y))
    glCalls().glVertex2s(x,y);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2s,glVertex2s(x,y))
}

void GLAPIENTRY glVertex2sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glVertex2sv,glVertex2sv(v))
    glCalls().glVertex2sv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex2sv,glVertex2sv(v))
}

void GLAPIENTRY glVertex3d(GLdouble x, GLdouble y, GLdouble z)
{
    gli().init();
    PREV_USER_CALL(glVertex3d,glVertex3d(x,y,z))
    glCalls().glVertex3d(x,y,z);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3d,glVertex3d(x,y,z))
}

void GLAPIENTRY glVertex3dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glVertex3dv,glVertex3dv(v))
    glCalls().glVertex3dv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3dv,glVertex3dv(v))
}

void GLAPIENTRY glVertex3f(GLfloat x, GLfloat y, GLfloat z)
{
    gli().init();
    PREV_USER_CALL(glVertex3f,glVertex3f(x,y,z))
    glCalls().glVertex3f(x,y,z);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3f,glVertex3f(x,y,z))
}

void GLAPIENTRY glVertex3fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glVertex3fv,glVertex3fv(v))
    glCalls().glVertex3fv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3fv,glVertex3fv(v))
}

void GLAPIENTRY glVertex3hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glVertex3hNV,glVertex3hNV(_p0,_p1,_p2))
    glCalls().glVertex3hNV(_p0,_p1,_p2);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3hNV,glVertex3hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertex3hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glVertex3hvNV,glVertex3hvNV(_p0))
    glCalls().glVertex3hvNV(_p0);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3hvNV,glVertex3hvNV(_p0))
}

void GLAPIENTRY glVertex3i(GLint x, GLint y, GLint z)
{
    gli().init();
    PREV_USER_CALL(glVertex3i,glVertex3i(x,y,z))
    glCalls().glVertex3i(x,y,z);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3i,glVertex3i(x,y,z))
}

void GLAPIENTRY glVertex3iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glVertex3iv,glVertex3iv(v))
    glCalls().glVertex3iv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3iv,glVertex3iv(v))
}

void GLAPIENTRY glVertex3s(GLshort x, GLshort y, GLshort z)
{
    gli().init();
    PREV_USER_CALL(glVertex3s,glVertex3s(x,y,z))
    glCalls().glVertex3s(x,y,z);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3s,glVertex3s(x,y,z))
}

void GLAPIENTRY glVertex3sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glVertex3sv,glVertex3sv(v))
    glCalls().glVertex3sv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex3sv,glVertex3sv(v))
}

void GLAPIENTRY glVertex4d(GLdouble x, GLdouble y, GLdouble z, GLdouble w)
{
    gli().init();
    PREV_USER_CALL(glVertex4d,glVertex4d(x,y,z,w))
    glCalls().glVertex4d(x,y,z,w);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4d,glVertex4d(x,y,z,w))
}

void GLAPIENTRY glVertex4dv(const GLdouble *v)
{
    gli().init();
    PREV_USER_CALL(glVertex4dv,glVertex4dv(v))
    glCalls().glVertex4dv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4dv,glVertex4dv(v))
}

void GLAPIENTRY glVertex4f(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
    gli().init();
    PREV_USER_CALL(glVertex4f,glVertex4f(x,y,z,w))
    glCalls().glVertex4f(x,y,z,w);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4f,glVertex4f(x,y,z,w))
}

void GLAPIENTRY glVertex4fv(const GLfloat *v)
{
    gli().init();
    PREV_USER_CALL(glVertex4fv,glVertex4fv(v))
    glCalls().glVertex4fv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4fv,glVertex4fv(v))
}

void GLAPIENTRY glVertex4hNV(GLhalfNV _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3)
{
    gli().init();
    PREV_USER_CALL(glVertex4hNV,glVertex4hNV(_p0,_p1,_p2,_p3))
    glCalls().glVertex4hNV(_p0,_p1,_p2,_p3);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4hNV,glVertex4hNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertex4hvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glVertex4hvNV,glVertex4hvNV(_p0))
    glCalls().glVertex4hvNV(_p0);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4hvNV,glVertex4hvNV(_p0))
}

void GLAPIENTRY glVertex4i(GLint x, GLint y, GLint z, GLint w)
{
    gli().init();
    PREV_USER_CALL(glVertex4i,glVertex4i(x,y,z,w))
    glCalls().glVertex4i(x,y,z,w);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4i,glVertex4i(x,y,z,w))
}

void GLAPIENTRY glVertex4iv(const GLint *v)
{
    gli().init();
    PREV_USER_CALL(glVertex4iv,glVertex4iv(v))
    glCalls().glVertex4iv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4iv,glVertex4iv(v))
}

void GLAPIENTRY glVertex4s(GLshort x, GLshort y, GLshort z, GLshort w)
{
    gli().init();
    PREV_USER_CALL(glVertex4s,glVertex4s(x,y,z,w))
    glCalls().glVertex4s(x,y,z,w);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4s,glVertex4s(x,y,z,w))
}

void GLAPIENTRY glVertex4sv(const GLshort *v)
{
    gli().init();
    PREV_USER_CALL(glVertex4sv,glVertex4sv(v))
    glCalls().glVertex4sv(v);
    gli().incVertexCount();
    POST_USER_CALL(glVertex4sv,glVertex4sv(v))
}

void GLAPIENTRY glVertexArrayParameteriAPPLE(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexArrayParameteriAPPLE,glVertexArrayParameteriAPPLE(_p0,_p1))
    glCalls().glVertexArrayParameteriAPPLE(_p0,_p1);
    POST_USER_CALL(glVertexArrayParameteriAPPLE,glVertexArrayParameteriAPPLE(_p0,_p1))
}

void GLAPIENTRY glVertexArrayRangeAPPLE(GLsizei _p0, GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexArrayRangeAPPLE,glVertexArrayRangeAPPLE(_p0,_p1))
    glCalls().glVertexArrayRangeAPPLE(_p0,_p1);
    POST_USER_CALL(glVertexArrayRangeAPPLE,glVertexArrayRangeAPPLE(_p0,_p1))
}

void GLAPIENTRY glVertexArrayRangeNV(GLsizei _p0, const GLvoid *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexArrayRangeNV,glVertexArrayRangeNV(_p0,_p1))
    glCalls().glVertexArrayRangeNV(_p0,_p1);
    POST_USER_CALL(glVertexArrayRangeNV,glVertexArrayRangeNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1d(GLuint _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1d,glVertexAttrib1d(_p0,_p1))
    glCalls().glVertexAttrib1d(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1d,glVertexAttrib1d(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1dARB(GLuint _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1dARB,glVertexAttrib1dARB(_p0,_p1))
    glCalls().glVertexAttrib1dARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1dARB,glVertexAttrib1dARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1dNV(GLuint _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1dNV,glVertexAttrib1dNV(_p0,_p1))
    glCalls().glVertexAttrib1dNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1dNV,glVertexAttrib1dNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1dv(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1dv,glVertexAttrib1dv(_p0,_p1))
    glCalls().glVertexAttrib1dv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1dv,glVertexAttrib1dv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1dvARB(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1dvARB,glVertexAttrib1dvARB(_p0,_p1))
    glCalls().glVertexAttrib1dvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1dvARB,glVertexAttrib1dvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1dvNV(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1dvNV,glVertexAttrib1dvNV(_p0,_p1))
    glCalls().glVertexAttrib1dvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1dvNV,glVertexAttrib1dvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1f(GLuint _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1f,glVertexAttrib1f(_p0,_p1))
    glCalls().glVertexAttrib1f(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1f,glVertexAttrib1f(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1fARB(GLuint _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1fARB,glVertexAttrib1fARB(_p0,_p1))
    glCalls().glVertexAttrib1fARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1fARB,glVertexAttrib1fARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1fNV(GLuint _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1fNV,glVertexAttrib1fNV(_p0,_p1))
    glCalls().glVertexAttrib1fNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1fNV,glVertexAttrib1fNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1fv(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1fv,glVertexAttrib1fv(_p0,_p1))
    glCalls().glVertexAttrib1fv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1fv,glVertexAttrib1fv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1fvARB(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1fvARB,glVertexAttrib1fvARB(_p0,_p1))
    glCalls().glVertexAttrib1fvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1fvARB,glVertexAttrib1fvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1fvNV(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1fvNV,glVertexAttrib1fvNV(_p0,_p1))
    glCalls().glVertexAttrib1fvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1fvNV,glVertexAttrib1fvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1hNV(GLuint _p0, GLhalfNV _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1hNV,glVertexAttrib1hNV(_p0,_p1))
    glCalls().glVertexAttrib1hNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1hNV,glVertexAttrib1hNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1hvNV(GLuint _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1hvNV,glVertexAttrib1hvNV(_p0,_p1))
    glCalls().glVertexAttrib1hvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1hvNV,glVertexAttrib1hvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1s(GLuint _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1s,glVertexAttrib1s(_p0,_p1))
    glCalls().glVertexAttrib1s(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1s,glVertexAttrib1s(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1sARB(GLuint _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1sARB,glVertexAttrib1sARB(_p0,_p1))
    glCalls().glVertexAttrib1sARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1sARB,glVertexAttrib1sARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1sNV(GLuint _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1sNV,glVertexAttrib1sNV(_p0,_p1))
    glCalls().glVertexAttrib1sNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1sNV,glVertexAttrib1sNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1sv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1sv,glVertexAttrib1sv(_p0,_p1))
    glCalls().glVertexAttrib1sv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1sv,glVertexAttrib1sv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1svARB(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1svARB,glVertexAttrib1svARB(_p0,_p1))
    glCalls().glVertexAttrib1svARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1svARB,glVertexAttrib1svARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib1svNV(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib1svNV,glVertexAttrib1svNV(_p0,_p1))
    glCalls().glVertexAttrib1svNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib1svNV,glVertexAttrib1svNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2d(GLuint _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2d,glVertexAttrib2d(_p0,_p1,_p2))
    glCalls().glVertexAttrib2d(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2d,glVertexAttrib2d(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2dARB(GLuint _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2dARB,glVertexAttrib2dARB(_p0,_p1,_p2))
    glCalls().glVertexAttrib2dARB(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2dARB,glVertexAttrib2dARB(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2dNV(GLuint _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2dNV,glVertexAttrib2dNV(_p0,_p1,_p2))
    glCalls().glVertexAttrib2dNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2dNV,glVertexAttrib2dNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2dv(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2dv,glVertexAttrib2dv(_p0,_p1))
    glCalls().glVertexAttrib2dv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2dv,glVertexAttrib2dv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2dvARB(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2dvARB,glVertexAttrib2dvARB(_p0,_p1))
    glCalls().glVertexAttrib2dvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2dvARB,glVertexAttrib2dvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2dvNV(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2dvNV,glVertexAttrib2dvNV(_p0,_p1))
    glCalls().glVertexAttrib2dvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2dvNV,glVertexAttrib2dvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2f(GLuint _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2f,glVertexAttrib2f(_p0,_p1,_p2))
    glCalls().glVertexAttrib2f(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2f,glVertexAttrib2f(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2fARB(GLuint _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2fARB,glVertexAttrib2fARB(_p0,_p1,_p2))
    glCalls().glVertexAttrib2fARB(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2fARB,glVertexAttrib2fARB(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2fNV(GLuint _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2fNV,glVertexAttrib2fNV(_p0,_p1,_p2))
    glCalls().glVertexAttrib2fNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2fNV,glVertexAttrib2fNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2fv(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2fv,glVertexAttrib2fv(_p0,_p1))
    glCalls().glVertexAttrib2fv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2fv,glVertexAttrib2fv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2fvARB(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2fvARB,glVertexAttrib2fvARB(_p0,_p1))
    glCalls().glVertexAttrib2fvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2fvARB,glVertexAttrib2fvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2fvNV(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2fvNV,glVertexAttrib2fvNV(_p0,_p1))
    glCalls().glVertexAttrib2fvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2fvNV,glVertexAttrib2fvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2hNV(GLuint _p0, GLhalfNV _p1, GLhalfNV _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2hNV,glVertexAttrib2hNV(_p0,_p1,_p2))
    glCalls().glVertexAttrib2hNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2hNV,glVertexAttrib2hNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2hvNV(GLuint _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2hvNV,glVertexAttrib2hvNV(_p0,_p1))
    glCalls().glVertexAttrib2hvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2hvNV,glVertexAttrib2hvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2s(GLuint _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2s,glVertexAttrib2s(_p0,_p1,_p2))
    glCalls().glVertexAttrib2s(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2s,glVertexAttrib2s(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2sARB(GLuint _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2sARB,glVertexAttrib2sARB(_p0,_p1,_p2))
    glCalls().glVertexAttrib2sARB(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2sARB,glVertexAttrib2sARB(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2sNV(GLuint _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2sNV,glVertexAttrib2sNV(_p0,_p1,_p2))
    glCalls().glVertexAttrib2sNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttrib2sNV,glVertexAttrib2sNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttrib2sv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2sv,glVertexAttrib2sv(_p0,_p1))
    glCalls().glVertexAttrib2sv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2sv,glVertexAttrib2sv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2svARB(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2svARB,glVertexAttrib2svARB(_p0,_p1))
    glCalls().glVertexAttrib2svARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2svARB,glVertexAttrib2svARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib2svNV(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib2svNV,glVertexAttrib2svNV(_p0,_p1))
    glCalls().glVertexAttrib2svNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib2svNV,glVertexAttrib2svNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3d(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3d,glVertexAttrib3d(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3d(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3d,glVertexAttrib3d(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3dARB(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3dARB,glVertexAttrib3dARB(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3dARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3dARB,glVertexAttrib3dARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3dNV(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3dNV,glVertexAttrib3dNV(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3dNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3dNV,glVertexAttrib3dNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3dv(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3dv,glVertexAttrib3dv(_p0,_p1))
    glCalls().glVertexAttrib3dv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3dv,glVertexAttrib3dv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3dvARB(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3dvARB,glVertexAttrib3dvARB(_p0,_p1))
    glCalls().glVertexAttrib3dvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3dvARB,glVertexAttrib3dvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3dvNV(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3dvNV,glVertexAttrib3dvNV(_p0,_p1))
    glCalls().glVertexAttrib3dvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3dvNV,glVertexAttrib3dvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3f(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3f,glVertexAttrib3f(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3f(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3f,glVertexAttrib3f(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3fARB(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3fARB,glVertexAttrib3fARB(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3fARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3fARB,glVertexAttrib3fARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3fNV(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3fNV,glVertexAttrib3fNV(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3fNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3fNV,glVertexAttrib3fNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3fv(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3fv,glVertexAttrib3fv(_p0,_p1))
    glCalls().glVertexAttrib3fv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3fv,glVertexAttrib3fv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3fvARB(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3fvARB,glVertexAttrib3fvARB(_p0,_p1))
    glCalls().glVertexAttrib3fvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3fvARB,glVertexAttrib3fvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3fvNV(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3fvNV,glVertexAttrib3fvNV(_p0,_p1))
    glCalls().glVertexAttrib3fvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3fvNV,glVertexAttrib3fvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3hNV(GLuint _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3hNV,glVertexAttrib3hNV(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3hNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3hNV,glVertexAttrib3hNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3hvNV(GLuint _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3hvNV,glVertexAttrib3hvNV(_p0,_p1))
    glCalls().glVertexAttrib3hvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3hvNV,glVertexAttrib3hvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3s(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3s,glVertexAttrib3s(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3s(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3s,glVertexAttrib3s(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3sARB(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3sARB,glVertexAttrib3sARB(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3sARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3sARB,glVertexAttrib3sARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3sNV(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3sNV,glVertexAttrib3sNV(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttrib3sNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttrib3sNV,glVertexAttrib3sNV(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttrib3sv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3sv,glVertexAttrib3sv(_p0,_p1))
    glCalls().glVertexAttrib3sv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3sv,glVertexAttrib3sv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3svARB(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3svARB,glVertexAttrib3svARB(_p0,_p1))
    glCalls().glVertexAttrib3svARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3svARB,glVertexAttrib3svARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib3svNV(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib3svNV,glVertexAttrib3svNV(_p0,_p1))
    glCalls().glVertexAttrib3svNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib3svNV,glVertexAttrib3svNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Nbv(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nbv,glVertexAttrib4Nbv(_p0,_p1))
    glCalls().glVertexAttrib4Nbv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Nbv,glVertexAttrib4Nbv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NbvARB(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NbvARB,glVertexAttrib4NbvARB(_p0,_p1))
    glCalls().glVertexAttrib4NbvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NbvARB,glVertexAttrib4NbvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Niv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Niv,glVertexAttrib4Niv(_p0,_p1))
    glCalls().glVertexAttrib4Niv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Niv,glVertexAttrib4Niv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NivARB(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NivARB,glVertexAttrib4NivARB(_p0,_p1))
    glCalls().glVertexAttrib4NivARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NivARB,glVertexAttrib4NivARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Nsv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nsv,glVertexAttrib4Nsv(_p0,_p1))
    glCalls().glVertexAttrib4Nsv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Nsv,glVertexAttrib4Nsv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NsvARB(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NsvARB,glVertexAttrib4NsvARB(_p0,_p1))
    glCalls().glVertexAttrib4NsvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NsvARB,glVertexAttrib4NsvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Nub(GLuint _p0, GLubyte _p1, GLubyte _p2, GLubyte _p3, GLubyte _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nub,glVertexAttrib4Nub(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4Nub(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4Nub,glVertexAttrib4Nub(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4NubARB(GLuint _p0, GLubyte _p1, GLubyte _p2, GLubyte _p3, GLubyte _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NubARB,glVertexAttrib4NubARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4NubARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4NubARB,glVertexAttrib4NubARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4Nubv(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nubv,glVertexAttrib4Nubv(_p0,_p1))
    glCalls().glVertexAttrib4Nubv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Nubv,glVertexAttrib4Nubv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NubvARB(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NubvARB,glVertexAttrib4NubvARB(_p0,_p1))
    glCalls().glVertexAttrib4NubvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NubvARB,glVertexAttrib4NubvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Nuiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nuiv,glVertexAttrib4Nuiv(_p0,_p1))
    glCalls().glVertexAttrib4Nuiv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Nuiv,glVertexAttrib4Nuiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NuivARB(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NuivARB,glVertexAttrib4NuivARB(_p0,_p1))
    glCalls().glVertexAttrib4NuivARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NuivARB,glVertexAttrib4NuivARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4Nusv(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4Nusv,glVertexAttrib4Nusv(_p0,_p1))
    glCalls().glVertexAttrib4Nusv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4Nusv,glVertexAttrib4Nusv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4NusvARB(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4NusvARB,glVertexAttrib4NusvARB(_p0,_p1))
    glCalls().glVertexAttrib4NusvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4NusvARB,glVertexAttrib4NusvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4bv(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4bv,glVertexAttrib4bv(_p0,_p1))
    glCalls().glVertexAttrib4bv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4bv,glVertexAttrib4bv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4bvARB(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4bvARB,glVertexAttrib4bvARB(_p0,_p1))
    glCalls().glVertexAttrib4bvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4bvARB,glVertexAttrib4bvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4d(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4d,glVertexAttrib4d(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4d(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4d,glVertexAttrib4d(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4dARB(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4dARB,glVertexAttrib4dARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4dARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4dARB,glVertexAttrib4dARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4dNV(GLuint _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4dNV,glVertexAttrib4dNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4dNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4dNV,glVertexAttrib4dNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4dv(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4dv,glVertexAttrib4dv(_p0,_p1))
    glCalls().glVertexAttrib4dv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4dv,glVertexAttrib4dv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4dvARB(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4dvARB,glVertexAttrib4dvARB(_p0,_p1))
    glCalls().glVertexAttrib4dvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4dvARB,glVertexAttrib4dvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4dvNV(GLuint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4dvNV,glVertexAttrib4dvNV(_p0,_p1))
    glCalls().glVertexAttrib4dvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4dvNV,glVertexAttrib4dvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4f(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4f,glVertexAttrib4f(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4f(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4f,glVertexAttrib4f(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4fARB(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4fARB,glVertexAttrib4fARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4fARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4fARB,glVertexAttrib4fARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4fNV(GLuint _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4fNV,glVertexAttrib4fNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4fNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4fNV,glVertexAttrib4fNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4fv(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4fv,glVertexAttrib4fv(_p0,_p1))
    glCalls().glVertexAttrib4fv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4fv,glVertexAttrib4fv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4fvARB(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4fvARB,glVertexAttrib4fvARB(_p0,_p1))
    glCalls().glVertexAttrib4fvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4fvARB,glVertexAttrib4fvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4fvNV(GLuint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4fvNV,glVertexAttrib4fvNV(_p0,_p1))
    glCalls().glVertexAttrib4fvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4fvNV,glVertexAttrib4fvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4hNV(GLuint _p0, GLhalfNV _p1, GLhalfNV _p2, GLhalfNV _p3, GLhalfNV _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4hNV,glVertexAttrib4hNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4hNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4hNV,glVertexAttrib4hNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4hvNV(GLuint _p0, const GLhalfNV *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4hvNV,glVertexAttrib4hvNV(_p0,_p1))
    glCalls().glVertexAttrib4hvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4hvNV,glVertexAttrib4hvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4iv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4iv,glVertexAttrib4iv(_p0,_p1))
    glCalls().glVertexAttrib4iv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4iv,glVertexAttrib4iv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4ivARB(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4ivARB,glVertexAttrib4ivARB(_p0,_p1))
    glCalls().glVertexAttrib4ivARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4ivARB,glVertexAttrib4ivARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4s(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3, GLshort _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4s,glVertexAttrib4s(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4s(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4s,glVertexAttrib4s(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4sARB(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3, GLshort _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4sARB,glVertexAttrib4sARB(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4sARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4sARB,glVertexAttrib4sARB(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4sNV(GLuint _p0, GLshort _p1, GLshort _p2, GLshort _p3, GLshort _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4sNV,glVertexAttrib4sNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4sNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4sNV,glVertexAttrib4sNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4sv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4sv,glVertexAttrib4sv(_p0,_p1))
    glCalls().glVertexAttrib4sv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4sv,glVertexAttrib4sv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4svARB(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4svARB,glVertexAttrib4svARB(_p0,_p1))
    glCalls().glVertexAttrib4svARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4svARB,glVertexAttrib4svARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4svNV(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4svNV,glVertexAttrib4svNV(_p0,_p1))
    glCalls().glVertexAttrib4svNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4svNV,glVertexAttrib4svNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4ubNV(GLuint _p0, GLubyte _p1, GLubyte _p2, GLubyte _p3, GLubyte _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4ubNV,glVertexAttrib4ubNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttrib4ubNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttrib4ubNV,glVertexAttrib4ubNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttrib4ubv(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4ubv,glVertexAttrib4ubv(_p0,_p1))
    glCalls().glVertexAttrib4ubv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4ubv,glVertexAttrib4ubv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4ubvARB(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4ubvARB,glVertexAttrib4ubvARB(_p0,_p1))
    glCalls().glVertexAttrib4ubvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4ubvARB,glVertexAttrib4ubvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4ubvNV(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4ubvNV,glVertexAttrib4ubvNV(_p0,_p1))
    glCalls().glVertexAttrib4ubvNV(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4ubvNV,glVertexAttrib4ubvNV(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4uiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4uiv,glVertexAttrib4uiv(_p0,_p1))
    glCalls().glVertexAttrib4uiv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4uiv,glVertexAttrib4uiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4uivARB(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4uivARB,glVertexAttrib4uivARB(_p0,_p1))
    glCalls().glVertexAttrib4uivARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4uivARB,glVertexAttrib4uivARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4usv(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4usv,glVertexAttrib4usv(_p0,_p1))
    glCalls().glVertexAttrib4usv(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4usv,glVertexAttrib4usv(_p0,_p1))
}

void GLAPIENTRY glVertexAttrib4usvARB(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttrib4usvARB,glVertexAttrib4usvARB(_p0,_p1))
    glCalls().glVertexAttrib4usvARB(_p0,_p1);
    POST_USER_CALL(glVertexAttrib4usvARB,glVertexAttrib4usvARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttribArrayObjectATI(GLuint _p0, GLint _p1, GLenum _p2, GLboolean _p3, GLsizei _p4, GLuint _p5, GLuint _p6)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribArrayObjectATI,glVertexAttribArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    glCalls().glVertexAttribArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(glVertexAttribArrayObjectATI,glVertexAttribArrayObjectATI(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
}

void GLAPIENTRY glVertexAttribDivisorARB(GLuint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribDivisorARB,glVertexAttribDivisorARB(_p0,_p1))
    glCalls().glVertexAttribDivisorARB(_p0,_p1);
    POST_USER_CALL(glVertexAttribDivisorARB,glVertexAttribDivisorARB(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1i(GLuint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1i,glVertexAttribI1i(_p0,_p1))
    glCalls().glVertexAttribI1i(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1i,glVertexAttribI1i(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1iEXT(GLuint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1iEXT,glVertexAttribI1iEXT(_p0,_p1))
    glCalls().glVertexAttribI1iEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1iEXT,glVertexAttribI1iEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1iv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1iv,glVertexAttribI1iv(_p0,_p1))
    glCalls().glVertexAttribI1iv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1iv,glVertexAttribI1iv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1ivEXT(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1ivEXT,glVertexAttribI1ivEXT(_p0,_p1))
    glCalls().glVertexAttribI1ivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1ivEXT,glVertexAttribI1ivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1ui(GLuint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1ui,glVertexAttribI1ui(_p0,_p1))
    glCalls().glVertexAttribI1ui(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1ui,glVertexAttribI1ui(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1uiEXT(GLuint _p0, GLuint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1uiEXT,glVertexAttribI1uiEXT(_p0,_p1))
    glCalls().glVertexAttribI1uiEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1uiEXT,glVertexAttribI1uiEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1uiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1uiv,glVertexAttribI1uiv(_p0,_p1))
    glCalls().glVertexAttribI1uiv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1uiv,glVertexAttribI1uiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI1uivEXT(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI1uivEXT,glVertexAttribI1uivEXT(_p0,_p1))
    glCalls().glVertexAttribI1uivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI1uivEXT,glVertexAttribI1uivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI2i(GLuint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2i,glVertexAttribI2i(_p0,_p1,_p2))
    glCalls().glVertexAttribI2i(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribI2i,glVertexAttribI2i(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribI2iEXT(GLuint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2iEXT,glVertexAttribI2iEXT(_p0,_p1,_p2))
    glCalls().glVertexAttribI2iEXT(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribI2iEXT,glVertexAttribI2iEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribI2iv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2iv,glVertexAttribI2iv(_p0,_p1))
    glCalls().glVertexAttribI2iv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI2iv,glVertexAttribI2iv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI2ivEXT(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2ivEXT,glVertexAttribI2ivEXT(_p0,_p1))
    glCalls().glVertexAttribI2ivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI2ivEXT,glVertexAttribI2ivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI2ui(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2ui,glVertexAttribI2ui(_p0,_p1,_p2))
    glCalls().glVertexAttribI2ui(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribI2ui,glVertexAttribI2ui(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribI2uiEXT(GLuint _p0, GLuint _p1, GLuint _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2uiEXT,glVertexAttribI2uiEXT(_p0,_p1,_p2))
    glCalls().glVertexAttribI2uiEXT(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribI2uiEXT,glVertexAttribI2uiEXT(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribI2uiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2uiv,glVertexAttribI2uiv(_p0,_p1))
    glCalls().glVertexAttribI2uiv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI2uiv,glVertexAttribI2uiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI2uivEXT(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI2uivEXT,glVertexAttribI2uivEXT(_p0,_p1))
    glCalls().glVertexAttribI2uivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI2uivEXT,glVertexAttribI2uivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI3i(GLuint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3i,glVertexAttribI3i(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttribI3i(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttribI3i,glVertexAttribI3i(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttribI3iEXT(GLuint _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3iEXT,glVertexAttribI3iEXT(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttribI3iEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttribI3iEXT,glVertexAttribI3iEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttribI3iv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3iv,glVertexAttribI3iv(_p0,_p1))
    glCalls().glVertexAttribI3iv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI3iv,glVertexAttribI3iv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI3ivEXT(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3ivEXT,glVertexAttribI3ivEXT(_p0,_p1))
    glCalls().glVertexAttribI3ivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI3ivEXT,glVertexAttribI3ivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI3ui(GLuint _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3ui,glVertexAttribI3ui(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttribI3ui(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttribI3ui,glVertexAttribI3ui(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttribI3uiEXT(GLuint _p0, GLuint _p1, GLuint _p2, GLuint _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3uiEXT,glVertexAttribI3uiEXT(_p0,_p1,_p2,_p3))
    glCalls().glVertexAttribI3uiEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexAttribI3uiEXT,glVertexAttribI3uiEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexAttribI3uiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3uiv,glVertexAttribI3uiv(_p0,_p1))
    glCalls().glVertexAttribI3uiv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI3uiv,glVertexAttribI3uiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI3uivEXT(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI3uivEXT,glVertexAttribI3uivEXT(_p0,_p1))
    glCalls().glVertexAttribI3uivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI3uivEXT,glVertexAttribI3uivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4bv(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4bv,glVertexAttribI4bv(_p0,_p1))
    glCalls().glVertexAttribI4bv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4bv,glVertexAttribI4bv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4bvEXT(GLuint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4bvEXT,glVertexAttribI4bvEXT(_p0,_p1))
    glCalls().glVertexAttribI4bvEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4bvEXT,glVertexAttribI4bvEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4i(GLuint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4i,glVertexAttribI4i(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribI4i(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribI4i,glVertexAttribI4i(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribI4iEXT(GLuint _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4iEXT,glVertexAttribI4iEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribI4iEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribI4iEXT,glVertexAttribI4iEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribI4iv(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4iv,glVertexAttribI4iv(_p0,_p1))
    glCalls().glVertexAttribI4iv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4iv,glVertexAttribI4iv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4ivEXT(GLuint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4ivEXT,glVertexAttribI4ivEXT(_p0,_p1))
    glCalls().glVertexAttribI4ivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4ivEXT,glVertexAttribI4ivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4sv(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4sv,glVertexAttribI4sv(_p0,_p1))
    glCalls().glVertexAttribI4sv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4sv,glVertexAttribI4sv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4svEXT(GLuint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4svEXT,glVertexAttribI4svEXT(_p0,_p1))
    glCalls().glVertexAttribI4svEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4svEXT,glVertexAttribI4svEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4ubv(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4ubv,glVertexAttribI4ubv(_p0,_p1))
    glCalls().glVertexAttribI4ubv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4ubv,glVertexAttribI4ubv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4ubvEXT(GLuint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4ubvEXT,glVertexAttribI4ubvEXT(_p0,_p1))
    glCalls().glVertexAttribI4ubvEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4ubvEXT,glVertexAttribI4ubvEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4ui(GLuint _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4ui,glVertexAttribI4ui(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribI4ui(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribI4ui,glVertexAttribI4ui(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribI4uiEXT(GLuint _p0, GLuint _p1, GLuint _p2, GLuint _p3, GLuint _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4uiEXT,glVertexAttribI4uiEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribI4uiEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribI4uiEXT,glVertexAttribI4uiEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribI4uiv(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4uiv,glVertexAttribI4uiv(_p0,_p1))
    glCalls().glVertexAttribI4uiv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4uiv,glVertexAttribI4uiv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4uivEXT(GLuint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4uivEXT,glVertexAttribI4uivEXT(_p0,_p1))
    glCalls().glVertexAttribI4uivEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4uivEXT,glVertexAttribI4uivEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4usv(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4usv,glVertexAttribI4usv(_p0,_p1))
    glCalls().glVertexAttribI4usv(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4usv,glVertexAttribI4usv(_p0,_p1))
}

void GLAPIENTRY glVertexAttribI4usvEXT(GLuint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribI4usvEXT,glVertexAttribI4usvEXT(_p0,_p1))
    glCalls().glVertexAttribI4usvEXT(_p0,_p1);
    POST_USER_CALL(glVertexAttribI4usvEXT,glVertexAttribI4usvEXT(_p0,_p1))
}

void GLAPIENTRY glVertexAttribIPointer(GLuint _p0, GLint _p1, GLenum _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribIPointer,glVertexAttribIPointer(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribIPointer(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribIPointer,glVertexAttribIPointer(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribIPointerEXT(GLuint _p0, GLint _p1, GLenum _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribIPointerEXT,glVertexAttribIPointerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribIPointerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribIPointerEXT,glVertexAttribIPointerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribPointer(GLuint _p0, GLint _p1, GLenum _p2, GLboolean _p3, GLsizei _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribPointer,glVertexAttribPointer(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glVertexAttribPointer(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glVertexAttribPointer,glVertexAttribPointer(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glVertexAttribPointerARB(GLuint _p0, GLint _p1, GLenum _p2, GLboolean _p3, GLsizei _p4, const GLvoid *_p5)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribPointerARB,glVertexAttribPointerARB(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glVertexAttribPointerARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glVertexAttribPointerARB,glVertexAttribPointerARB(_p0,_p1,_p2,_p3,_p4,_p5))
}

void GLAPIENTRY glVertexAttribPointerNV(GLuint _p0, GLint _p1, GLenum _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribPointerNV,glVertexAttribPointerNV(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexAttribPointerNV(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexAttribPointerNV,glVertexAttribPointerNV(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexAttribs1dvNV(GLuint _p0, GLsizei _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs1dvNV,glVertexAttribs1dvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs1dvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs1dvNV,glVertexAttribs1dvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs1fvNV(GLuint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs1fvNV,glVertexAttribs1fvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs1fvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs1fvNV,glVertexAttribs1fvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs1hvNV(GLuint _p0, GLsizei _p1, const GLhalfNV *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs1hvNV,glVertexAttribs1hvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs1hvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs1hvNV,glVertexAttribs1hvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs1svNV(GLuint _p0, GLsizei _p1, const GLshort *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs1svNV,glVertexAttribs1svNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs1svNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs1svNV,glVertexAttribs1svNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs2dvNV(GLuint _p0, GLsizei _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs2dvNV,glVertexAttribs2dvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs2dvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs2dvNV,glVertexAttribs2dvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs2fvNV(GLuint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs2fvNV,glVertexAttribs2fvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs2fvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs2fvNV,glVertexAttribs2fvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs2hvNV(GLuint _p0, GLsizei _p1, const GLhalfNV *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs2hvNV,glVertexAttribs2hvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs2hvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs2hvNV,glVertexAttribs2hvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs2svNV(GLuint _p0, GLsizei _p1, const GLshort *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs2svNV,glVertexAttribs2svNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs2svNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs2svNV,glVertexAttribs2svNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs3dvNV(GLuint _p0, GLsizei _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs3dvNV,glVertexAttribs3dvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs3dvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs3dvNV,glVertexAttribs3dvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs3fvNV(GLuint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs3fvNV,glVertexAttribs3fvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs3fvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs3fvNV,glVertexAttribs3fvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs3hvNV(GLuint _p0, GLsizei _p1, const GLhalfNV *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs3hvNV,glVertexAttribs3hvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs3hvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs3hvNV,glVertexAttribs3hvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs3svNV(GLuint _p0, GLsizei _p1, const GLshort *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs3svNV,glVertexAttribs3svNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs3svNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs3svNV,glVertexAttribs3svNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs4dvNV(GLuint _p0, GLsizei _p1, const GLdouble *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs4dvNV,glVertexAttribs4dvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs4dvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs4dvNV,glVertexAttribs4dvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs4fvNV(GLuint _p0, GLsizei _p1, const GLfloat *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs4fvNV,glVertexAttribs4fvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs4fvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs4fvNV,glVertexAttribs4fvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs4hvNV(GLuint _p0, GLsizei _p1, const GLhalfNV *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs4hvNV,glVertexAttribs4hvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs4hvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs4hvNV,glVertexAttribs4hvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs4svNV(GLuint _p0, GLsizei _p1, const GLshort *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs4svNV,glVertexAttribs4svNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs4svNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs4svNV,glVertexAttribs4svNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexAttribs4ubvNV(GLuint _p0, GLsizei _p1, const GLubyte *_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexAttribs4ubvNV,glVertexAttribs4ubvNV(_p0,_p1,_p2))
    glCalls().glVertexAttribs4ubvNV(_p0,_p1,_p2);
    POST_USER_CALL(glVertexAttribs4ubvNV,glVertexAttribs4ubvNV(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexBlendARB(GLint _p0)
{
    gli().init();
    PREV_USER_CALL(glVertexBlendARB,glVertexBlendARB(_p0))
    glCalls().glVertexBlendARB(_p0);
    POST_USER_CALL(glVertexBlendARB,glVertexBlendARB(_p0))
}

void GLAPIENTRY glVertexBlendEnvfATI(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexBlendEnvfATI,glVertexBlendEnvfATI(_p0,_p1))
    glCalls().glVertexBlendEnvfATI(_p0,_p1);
    POST_USER_CALL(glVertexBlendEnvfATI,glVertexBlendEnvfATI(_p0,_p1))
}

void GLAPIENTRY glVertexBlendEnviATI(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexBlendEnviATI,glVertexBlendEnviATI(_p0,_p1))
    glCalls().glVertexBlendEnviATI(_p0,_p1);
    POST_USER_CALL(glVertexBlendEnviATI,glVertexBlendEnviATI(_p0,_p1))
}

void GLAPIENTRY glVertexPointer(GLint size, GLenum type, GLsizei stride, const GLvoid *ptr)
{
    gli().init();
    PREV_USER_CALL(glVertexPointer,glVertexPointer(size,type,stride,ptr))
    glCalls().glVertexPointer(size,type,stride,ptr);
    POST_USER_CALL(glVertexPointer,glVertexPointer(size,type,stride,ptr))
}

void GLAPIENTRY glVertexPointerEXT(GLint _p0, GLenum _p1, GLsizei _p2, GLsizei _p3, const GLvoid *_p4)
{
    gli().init();
    PREV_USER_CALL(glVertexPointerEXT,glVertexPointerEXT(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexPointerEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexPointerEXT,glVertexPointerEXT(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexPointervINTEL(GLint _p0, GLenum _p1, const GLvoid **_p2)
{
    gli().init();
    PREV_USER_CALL(glVertexPointervINTEL,glVertexPointervINTEL(_p0,_p1,_p2))
    glCalls().glVertexPointervINTEL(_p0,_p1,_p2);
    POST_USER_CALL(glVertexPointervINTEL,glVertexPointervINTEL(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexStream1dATI(GLenum _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1dATI,glVertexStream1dATI(_p0,_p1))
    glCalls().glVertexStream1dATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1dATI,glVertexStream1dATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1dvATI(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1dvATI,glVertexStream1dvATI(_p0,_p1))
    glCalls().glVertexStream1dvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1dvATI,glVertexStream1dvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1fATI(GLenum _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1fATI,glVertexStream1fATI(_p0,_p1))
    glCalls().glVertexStream1fATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1fATI,glVertexStream1fATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1fvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1fvATI,glVertexStream1fvATI(_p0,_p1))
    glCalls().glVertexStream1fvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1fvATI,glVertexStream1fvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1iATI(GLenum _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1iATI,glVertexStream1iATI(_p0,_p1))
    glCalls().glVertexStream1iATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1iATI,glVertexStream1iATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1ivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1ivATI,glVertexStream1ivATI(_p0,_p1))
    glCalls().glVertexStream1ivATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1ivATI,glVertexStream1ivATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1sATI(GLenum _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1sATI,glVertexStream1sATI(_p0,_p1))
    glCalls().glVertexStream1sATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1sATI,glVertexStream1sATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream1svATI(GLenum _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream1svATI,glVertexStream1svATI(_p0,_p1))
    glCalls().glVertexStream1svATI(_p0,_p1);
    POST_USER_CALL(glVertexStream1svATI,glVertexStream1svATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream2dATI(GLenum _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2dATI,glVertexStream2dATI(_p0,_p1,_p2))
    glCalls().glVertexStream2dATI(_p0,_p1,_p2);
    POST_USER_CALL(glVertexStream2dATI,glVertexStream2dATI(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexStream2dvATI(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2dvATI,glVertexStream2dvATI(_p0,_p1))
    glCalls().glVertexStream2dvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream2dvATI,glVertexStream2dvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream2fATI(GLenum _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2fATI,glVertexStream2fATI(_p0,_p1,_p2))
    glCalls().glVertexStream2fATI(_p0,_p1,_p2);
    POST_USER_CALL(glVertexStream2fATI,glVertexStream2fATI(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexStream2fvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2fvATI,glVertexStream2fvATI(_p0,_p1))
    glCalls().glVertexStream2fvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream2fvATI,glVertexStream2fvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream2iATI(GLenum _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2iATI,glVertexStream2iATI(_p0,_p1,_p2))
    glCalls().glVertexStream2iATI(_p0,_p1,_p2);
    POST_USER_CALL(glVertexStream2iATI,glVertexStream2iATI(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexStream2ivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2ivATI,glVertexStream2ivATI(_p0,_p1))
    glCalls().glVertexStream2ivATI(_p0,_p1);
    POST_USER_CALL(glVertexStream2ivATI,glVertexStream2ivATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream2sATI(GLenum _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2sATI,glVertexStream2sATI(_p0,_p1,_p2))
    glCalls().glVertexStream2sATI(_p0,_p1,_p2);
    POST_USER_CALL(glVertexStream2sATI,glVertexStream2sATI(_p0,_p1,_p2))
}

void GLAPIENTRY glVertexStream2svATI(GLenum _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream2svATI,glVertexStream2svATI(_p0,_p1))
    glCalls().glVertexStream2svATI(_p0,_p1);
    POST_USER_CALL(glVertexStream2svATI,glVertexStream2svATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream3dATI(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3dATI,glVertexStream3dATI(_p0,_p1,_p2,_p3))
    glCalls().glVertexStream3dATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexStream3dATI,glVertexStream3dATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexStream3dvATI(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3dvATI,glVertexStream3dvATI(_p0,_p1))
    glCalls().glVertexStream3dvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream3dvATI,glVertexStream3dvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream3fATI(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3fATI,glVertexStream3fATI(_p0,_p1,_p2,_p3))
    glCalls().glVertexStream3fATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexStream3fATI,glVertexStream3fATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexStream3fvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3fvATI,glVertexStream3fvATI(_p0,_p1))
    glCalls().glVertexStream3fvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream3fvATI,glVertexStream3fvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream3iATI(GLenum _p0, GLint _p1, GLint _p2, GLint _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3iATI,glVertexStream3iATI(_p0,_p1,_p2,_p3))
    glCalls().glVertexStream3iATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexStream3iATI,glVertexStream3iATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexStream3ivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3ivATI,glVertexStream3ivATI(_p0,_p1))
    glCalls().glVertexStream3ivATI(_p0,_p1);
    POST_USER_CALL(glVertexStream3ivATI,glVertexStream3ivATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream3sATI(GLenum _p0, GLshort _p1, GLshort _p2, GLshort _p3)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3sATI,glVertexStream3sATI(_p0,_p1,_p2,_p3))
    glCalls().glVertexStream3sATI(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexStream3sATI,glVertexStream3sATI(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexStream3svATI(GLenum _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream3svATI,glVertexStream3svATI(_p0,_p1))
    glCalls().glVertexStream3svATI(_p0,_p1);
    POST_USER_CALL(glVertexStream3svATI,glVertexStream3svATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream4dATI(GLenum _p0, GLdouble _p1, GLdouble _p2, GLdouble _p3, GLdouble _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4dATI,glVertexStream4dATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexStream4dATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexStream4dATI,glVertexStream4dATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexStream4dvATI(GLenum _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4dvATI,glVertexStream4dvATI(_p0,_p1))
    glCalls().glVertexStream4dvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream4dvATI,glVertexStream4dvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream4fATI(GLenum _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3, GLfloat _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4fATI,glVertexStream4fATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexStream4fATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexStream4fATI,glVertexStream4fATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexStream4fvATI(GLenum _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4fvATI,glVertexStream4fvATI(_p0,_p1))
    glCalls().glVertexStream4fvATI(_p0,_p1);
    POST_USER_CALL(glVertexStream4fvATI,glVertexStream4fvATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream4iATI(GLenum _p0, GLint _p1, GLint _p2, GLint _p3, GLint _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4iATI,glVertexStream4iATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexStream4iATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexStream4iATI,glVertexStream4iATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexStream4ivATI(GLenum _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4ivATI,glVertexStream4ivATI(_p0,_p1))
    glCalls().glVertexStream4ivATI(_p0,_p1);
    POST_USER_CALL(glVertexStream4ivATI,glVertexStream4ivATI(_p0,_p1))
}

void GLAPIENTRY glVertexStream4sATI(GLenum _p0, GLshort _p1, GLshort _p2, GLshort _p3, GLshort _p4)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4sATI,glVertexStream4sATI(_p0,_p1,_p2,_p3,_p4))
    glCalls().glVertexStream4sATI(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(glVertexStream4sATI,glVertexStream4sATI(_p0,_p1,_p2,_p3,_p4))
}

void GLAPIENTRY glVertexStream4svATI(GLenum _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glVertexStream4svATI,glVertexStream4svATI(_p0,_p1))
    glCalls().glVertexStream4svATI(_p0,_p1);
    POST_USER_CALL(glVertexStream4svATI,glVertexStream4svATI(_p0,_p1))
}

void GLAPIENTRY glVertexWeightPointerEXT(GLsizei _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glVertexWeightPointerEXT,glVertexWeightPointerEXT(_p0,_p1,_p2,_p3))
    glCalls().glVertexWeightPointerEXT(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glVertexWeightPointerEXT,glVertexWeightPointerEXT(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glVertexWeightfEXT(GLfloat _p0)
{
    gli().init();
    PREV_USER_CALL(glVertexWeightfEXT,glVertexWeightfEXT(_p0))
    glCalls().glVertexWeightfEXT(_p0);
    POST_USER_CALL(glVertexWeightfEXT,glVertexWeightfEXT(_p0))
}

void GLAPIENTRY glVertexWeightfvEXT(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glVertexWeightfvEXT,glVertexWeightfvEXT(_p0))
    glCalls().glVertexWeightfvEXT(_p0);
    POST_USER_CALL(glVertexWeightfvEXT,glVertexWeightfvEXT(_p0))
}

void GLAPIENTRY glVertexWeighthNV(GLhalfNV _p0)
{
    gli().init();
    PREV_USER_CALL(glVertexWeighthNV,glVertexWeighthNV(_p0))
    glCalls().glVertexWeighthNV(_p0);
    POST_USER_CALL(glVertexWeighthNV,glVertexWeighthNV(_p0))
}

void GLAPIENTRY glVertexWeighthvNV(const GLhalfNV *_p0)
{
    gli().init();
    PREV_USER_CALL(glVertexWeighthvNV,glVertexWeighthvNV(_p0))
    glCalls().glVertexWeighthvNV(_p0);
    POST_USER_CALL(glVertexWeighthvNV,glVertexWeighthvNV(_p0))
}

void GLAPIENTRY glViewport(GLint x, GLint y, GLsizei width, GLsizei height)
{
    gli().init();
    PREV_USER_CALL(glViewport,glViewport(x,y,width,height))
    glCalls().glViewport(x,y,width,height);
    POST_USER_CALL(glViewport,glViewport(x,y,width,height))
}

void GLAPIENTRY glWeightPointerARB(GLint _p0, GLenum _p1, GLsizei _p2, const GLvoid *_p3)
{
    gli().init();
    PREV_USER_CALL(glWeightPointerARB,glWeightPointerARB(_p0,_p1,_p2,_p3))
    glCalls().glWeightPointerARB(_p0,_p1,_p2,_p3);
    POST_USER_CALL(glWeightPointerARB,glWeightPointerARB(_p0,_p1,_p2,_p3))
}

void GLAPIENTRY glWeightbvARB(GLint _p0, const GLbyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightbvARB,glWeightbvARB(_p0,_p1))
    glCalls().glWeightbvARB(_p0,_p1);
    POST_USER_CALL(glWeightbvARB,glWeightbvARB(_p0,_p1))
}

void GLAPIENTRY glWeightdvARB(GLint _p0, const GLdouble *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightdvARB,glWeightdvARB(_p0,_p1))
    glCalls().glWeightdvARB(_p0,_p1);
    POST_USER_CALL(glWeightdvARB,glWeightdvARB(_p0,_p1))
}

void GLAPIENTRY glWeightfvARB(GLint _p0, const GLfloat *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightfvARB,glWeightfvARB(_p0,_p1))
    glCalls().glWeightfvARB(_p0,_p1);
    POST_USER_CALL(glWeightfvARB,glWeightfvARB(_p0,_p1))
}

void GLAPIENTRY glWeightivARB(GLint _p0, const GLint *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightivARB,glWeightivARB(_p0,_p1))
    glCalls().glWeightivARB(_p0,_p1);
    POST_USER_CALL(glWeightivARB,glWeightivARB(_p0,_p1))
}

void GLAPIENTRY glWeightsvARB(GLint _p0, const GLshort *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightsvARB,glWeightsvARB(_p0,_p1))
    glCalls().glWeightsvARB(_p0,_p1);
    POST_USER_CALL(glWeightsvARB,glWeightsvARB(_p0,_p1))
}

void GLAPIENTRY glWeightubvARB(GLint _p0, const GLubyte *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightubvARB,glWeightubvARB(_p0,_p1))
    glCalls().glWeightubvARB(_p0,_p1);
    POST_USER_CALL(glWeightubvARB,glWeightubvARB(_p0,_p1))
}

void GLAPIENTRY glWeightuivARB(GLint _p0, const GLuint *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightuivARB,glWeightuivARB(_p0,_p1))
    glCalls().glWeightuivARB(_p0,_p1);
    POST_USER_CALL(glWeightuivARB,glWeightuivARB(_p0,_p1))
}

void GLAPIENTRY glWeightusvARB(GLint _p0, const GLushort *_p1)
{
    gli().init();
    PREV_USER_CALL(glWeightusvARB,glWeightusvARB(_p0,_p1))
    glCalls().glWeightusvARB(_p0,_p1);
    POST_USER_CALL(glWeightusvARB,glWeightusvARB(_p0,_p1))
}

void GLAPIENTRY glWindowPos2d(GLdouble _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2d,glWindowPos2d(_p0,_p1))
    glCalls().glWindowPos2d(_p0,_p1);
    POST_USER_CALL(glWindowPos2d,glWindowPos2d(_p0,_p1))
}

void GLAPIENTRY glWindowPos2dARB(GLdouble _p0, GLdouble _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2dARB,glWindowPos2dARB(_p0,_p1))
    glCalls().glWindowPos2dARB(_p0,_p1);
    POST_USER_CALL(glWindowPos2dARB,glWindowPos2dARB(_p0,_p1))
}

void GLAPIENTRY glWindowPos2dv(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2dv,glWindowPos2dv(_p0))
    glCalls().glWindowPos2dv(_p0);
    POST_USER_CALL(glWindowPos2dv,glWindowPos2dv(_p0))
}

void GLAPIENTRY glWindowPos2dvARB(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2dvARB,glWindowPos2dvARB(_p0))
    glCalls().glWindowPos2dvARB(_p0);
    POST_USER_CALL(glWindowPos2dvARB,glWindowPos2dvARB(_p0))
}

void GLAPIENTRY glWindowPos2f(GLfloat _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2f,glWindowPos2f(_p0,_p1))
    glCalls().glWindowPos2f(_p0,_p1);
    POST_USER_CALL(glWindowPos2f,glWindowPos2f(_p0,_p1))
}

void GLAPIENTRY glWindowPos2fARB(GLfloat _p0, GLfloat _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2fARB,glWindowPos2fARB(_p0,_p1))
    glCalls().glWindowPos2fARB(_p0,_p1);
    POST_USER_CALL(glWindowPos2fARB,glWindowPos2fARB(_p0,_p1))
}

void GLAPIENTRY glWindowPos2fv(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2fv,glWindowPos2fv(_p0))
    glCalls().glWindowPos2fv(_p0);
    POST_USER_CALL(glWindowPos2fv,glWindowPos2fv(_p0))
}

void GLAPIENTRY glWindowPos2fvARB(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2fvARB,glWindowPos2fvARB(_p0))
    glCalls().glWindowPos2fvARB(_p0);
    POST_USER_CALL(glWindowPos2fvARB,glWindowPos2fvARB(_p0))
}

void GLAPIENTRY glWindowPos2i(GLint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2i,glWindowPos2i(_p0,_p1))
    glCalls().glWindowPos2i(_p0,_p1);
    POST_USER_CALL(glWindowPos2i,glWindowPos2i(_p0,_p1))
}

void GLAPIENTRY glWindowPos2iARB(GLint _p0, GLint _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2iARB,glWindowPos2iARB(_p0,_p1))
    glCalls().glWindowPos2iARB(_p0,_p1);
    POST_USER_CALL(glWindowPos2iARB,glWindowPos2iARB(_p0,_p1))
}

void GLAPIENTRY glWindowPos2iv(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2iv,glWindowPos2iv(_p0))
    glCalls().glWindowPos2iv(_p0);
    POST_USER_CALL(glWindowPos2iv,glWindowPos2iv(_p0))
}

void GLAPIENTRY glWindowPos2ivARB(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2ivARB,glWindowPos2ivARB(_p0))
    glCalls().glWindowPos2ivARB(_p0);
    POST_USER_CALL(glWindowPos2ivARB,glWindowPos2ivARB(_p0))
}

void GLAPIENTRY glWindowPos2s(GLshort _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2s,glWindowPos2s(_p0,_p1))
    glCalls().glWindowPos2s(_p0,_p1);
    POST_USER_CALL(glWindowPos2s,glWindowPos2s(_p0,_p1))
}

void GLAPIENTRY glWindowPos2sARB(GLshort _p0, GLshort _p1)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2sARB,glWindowPos2sARB(_p0,_p1))
    glCalls().glWindowPos2sARB(_p0,_p1);
    POST_USER_CALL(glWindowPos2sARB,glWindowPos2sARB(_p0,_p1))
}

void GLAPIENTRY glWindowPos2sv(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2sv,glWindowPos2sv(_p0))
    glCalls().glWindowPos2sv(_p0);
    POST_USER_CALL(glWindowPos2sv,glWindowPos2sv(_p0))
}

void GLAPIENTRY glWindowPos2svARB(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos2svARB,glWindowPos2svARB(_p0))
    glCalls().glWindowPos2svARB(_p0);
    POST_USER_CALL(glWindowPos2svARB,glWindowPos2svARB(_p0))
}

void GLAPIENTRY glWindowPos3d(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3d,glWindowPos3d(_p0,_p1,_p2))
    glCalls().glWindowPos3d(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3d,glWindowPos3d(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3dARB(GLdouble _p0, GLdouble _p1, GLdouble _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3dARB,glWindowPos3dARB(_p0,_p1,_p2))
    glCalls().glWindowPos3dARB(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3dARB,glWindowPos3dARB(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3dv(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3dv,glWindowPos3dv(_p0))
    glCalls().glWindowPos3dv(_p0);
    POST_USER_CALL(glWindowPos3dv,glWindowPos3dv(_p0))
}

void GLAPIENTRY glWindowPos3dvARB(const GLdouble *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3dvARB,glWindowPos3dvARB(_p0))
    glCalls().glWindowPos3dvARB(_p0);
    POST_USER_CALL(glWindowPos3dvARB,glWindowPos3dvARB(_p0))
}

void GLAPIENTRY glWindowPos3f(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3f,glWindowPos3f(_p0,_p1,_p2))
    glCalls().glWindowPos3f(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3f,glWindowPos3f(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3fARB(GLfloat _p0, GLfloat _p1, GLfloat _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3fARB,glWindowPos3fARB(_p0,_p1,_p2))
    glCalls().glWindowPos3fARB(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3fARB,glWindowPos3fARB(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3fv(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3fv,glWindowPos3fv(_p0))
    glCalls().glWindowPos3fv(_p0);
    POST_USER_CALL(glWindowPos3fv,glWindowPos3fv(_p0))
}

void GLAPIENTRY glWindowPos3fvARB(const GLfloat *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3fvARB,glWindowPos3fvARB(_p0))
    glCalls().glWindowPos3fvARB(_p0);
    POST_USER_CALL(glWindowPos3fvARB,glWindowPos3fvARB(_p0))
}

void GLAPIENTRY glWindowPos3i(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3i,glWindowPos3i(_p0,_p1,_p2))
    glCalls().glWindowPos3i(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3i,glWindowPos3i(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3iARB(GLint _p0, GLint _p1, GLint _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3iARB,glWindowPos3iARB(_p0,_p1,_p2))
    glCalls().glWindowPos3iARB(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3iARB,glWindowPos3iARB(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3iv(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3iv,glWindowPos3iv(_p0))
    glCalls().glWindowPos3iv(_p0);
    POST_USER_CALL(glWindowPos3iv,glWindowPos3iv(_p0))
}

void GLAPIENTRY glWindowPos3ivARB(const GLint *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3ivARB,glWindowPos3ivARB(_p0))
    glCalls().glWindowPos3ivARB(_p0);
    POST_USER_CALL(glWindowPos3ivARB,glWindowPos3ivARB(_p0))
}

void GLAPIENTRY glWindowPos3s(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3s,glWindowPos3s(_p0,_p1,_p2))
    glCalls().glWindowPos3s(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3s,glWindowPos3s(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3sARB(GLshort _p0, GLshort _p1, GLshort _p2)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3sARB,glWindowPos3sARB(_p0,_p1,_p2))
    glCalls().glWindowPos3sARB(_p0,_p1,_p2);
    POST_USER_CALL(glWindowPos3sARB,glWindowPos3sARB(_p0,_p1,_p2))
}

void GLAPIENTRY glWindowPos3sv(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3sv,glWindowPos3sv(_p0))
    glCalls().glWindowPos3sv(_p0);
    POST_USER_CALL(glWindowPos3sv,glWindowPos3sv(_p0))
}

void GLAPIENTRY glWindowPos3svARB(const GLshort *_p0)
{
    gli().init();
    PREV_USER_CALL(glWindowPos3svARB,glWindowPos3svARB(_p0))
    glCalls().glWindowPos3svARB(_p0);
    POST_USER_CALL(glWindowPos3svARB,glWindowPos3svARB(_p0))
}

void GLAPIENTRY glWriteMaskEXT(GLuint _p0, GLuint _p1, GLenum _p2, GLenum _p3, GLenum _p4, GLenum _p5)
{
    gli().init();
    PREV_USER_CALL(glWriteMaskEXT,glWriteMaskEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    glCalls().glWriteMaskEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(glWriteMaskEXT,glWriteMaskEXT(_p0,_p1,_p2,_p3,_p4,_p5))
}

void * GLAPIENTRY wglAllocateMemoryNV(GLsizei _p0, GLfloat _p1, GLfloat _p2, GLfloat _p3)
{
    gli().init();
    void *_result;
    PREV_USER_CALL(wglAllocateMemoryNV,wglAllocateMemoryNV(_p0,_p1,_p2,_p3))
    _result = glCalls().wglAllocateMemoryNV(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglAllocateMemoryNV,wglAllocateMemoryNV(_p0,_p1,_p2,_p3))
    return _result;
}

BOOL GLAPIENTRY wglAssociateImageBufferEventsI3D(HDC _p0, const HANDLE *_p1, const LPVOID *_p2, const DWORD *_p3, UINT _p4)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglAssociateImageBufferEventsI3D,wglAssociateImageBufferEventsI3D(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglAssociateImageBufferEventsI3D(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglAssociateImageBufferEventsI3D,wglAssociateImageBufferEventsI3D(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglBeginFrameTrackingI3D()
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglBeginFrameTrackingI3D,wglBeginFrameTrackingI3D())
    _result = glCalls().wglBeginFrameTrackingI3D();
    POST_USER_CALL(wglBeginFrameTrackingI3D,wglBeginFrameTrackingI3D())
    return _result;
}

GLboolean GLAPIENTRY wglBindDisplayColorTableEXT(GLushort _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(wglBindDisplayColorTableEXT,wglBindDisplayColorTableEXT(_p0))
    _result = glCalls().wglBindDisplayColorTableEXT(_p0);
    POST_USER_CALL(wglBindDisplayColorTableEXT,wglBindDisplayColorTableEXT(_p0))
    return _result;
}

BOOL GLAPIENTRY wglBindTexImageARB(HPBUFFERARB _p0, int _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglBindTexImageARB,wglBindTexImageARB(_p0,_p1))
    _result = glCalls().wglBindTexImageARB(_p0,_p1);
    POST_USER_CALL(wglBindTexImageARB,wglBindTexImageARB(_p0,_p1))
    return _result;
}

int GLAPIENTRY wglChoosePixelFormat(HDC _p0, const PIXELFORMATDESCRIPTOR *_p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglChoosePixelFormat,wglChoosePixelFormat(_p0,_p1))
    _result = glCalls().wglChoosePixelFormat(_p0,_p1);
    POST_USER_CALL(wglChoosePixelFormat,wglChoosePixelFormat(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglChoosePixelFormatARB(HDC _p0, const int *_p1, const FLOAT *_p2, UINT _p3, int *_p4, UINT *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglChoosePixelFormatARB,wglChoosePixelFormatARB(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglChoosePixelFormatARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglChoosePixelFormatARB,wglChoosePixelFormatARB(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

BOOL GLAPIENTRY wglChoosePixelFormatEXT(HDC _p0, const int *_p1, const FLOAT *_p2, UINT _p3, int *_p4, UINT *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglChoosePixelFormatEXT,wglChoosePixelFormatEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglChoosePixelFormatEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglChoosePixelFormatEXT,wglChoosePixelFormatEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

int GLAPIENTRY wglCopyContext(HGLRC _p0, HGLRC _p1, unsigned int _p2)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglCopyContext,wglCopyContext(_p0,_p1,_p2))
    _result = glCalls().wglCopyContext(_p0,_p1,_p2);
    POST_USER_CALL(wglCopyContext,wglCopyContext(_p0,_p1,_p2))
    return _result;
}

HANDLE GLAPIENTRY wglCreateBufferRegionARB(HDC _p0, int _p1, UINT _p2)
{
    gli().init();
    HANDLE _result;
    PREV_USER_CALL(wglCreateBufferRegionARB,wglCreateBufferRegionARB(_p0,_p1,_p2))
    _result = glCalls().wglCreateBufferRegionARB(_p0,_p1,_p2);
    POST_USER_CALL(wglCreateBufferRegionARB,wglCreateBufferRegionARB(_p0,_p1,_p2))
    return _result;
}

HGLRC GLAPIENTRY wglCreateContext(HDC _p0)
{
    gli().init();
    HGLRC _result;
    PREV_USER_CALL(wglCreateContext,wglCreateContext(_p0))
    _result = glCalls().wglCreateContext(_p0);
    POST_USER_CALL(wglCreateContext,wglCreateContext(_p0))
    return _result;
}

GLboolean GLAPIENTRY wglCreateDisplayColorTableEXT(GLushort _p0)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(wglCreateDisplayColorTableEXT,wglCreateDisplayColorTableEXT(_p0))
    _result = glCalls().wglCreateDisplayColorTableEXT(_p0);
    POST_USER_CALL(wglCreateDisplayColorTableEXT,wglCreateDisplayColorTableEXT(_p0))
    return _result;
}

LPVOID GLAPIENTRY wglCreateImageBufferI3D(HDC _p0, DWORD _p1, UINT _p2)
{
    gli().init();
    LPVOID _result;
    PREV_USER_CALL(wglCreateImageBufferI3D,wglCreateImageBufferI3D(_p0,_p1,_p2))
    _result = glCalls().wglCreateImageBufferI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglCreateImageBufferI3D,wglCreateImageBufferI3D(_p0,_p1,_p2))
    return _result;
}

HGLRC GLAPIENTRY wglCreateLayerContext(HDC _p0, int _p1)
{
    gli().init();
    HGLRC _result;
    PREV_USER_CALL(wglCreateLayerContext,wglCreateLayerContext(_p0,_p1))
    _result = glCalls().wglCreateLayerContext(_p0,_p1);
    POST_USER_CALL(wglCreateLayerContext,wglCreateLayerContext(_p0,_p1))
    return _result;
}

HPBUFFERARB GLAPIENTRY wglCreatePbufferARB(HDC _p0, int _p1, int _p2, int _p3, const int *_p4)
{
    gli().init();
    HPBUFFERARB _result;
    PREV_USER_CALL(wglCreatePbufferARB,wglCreatePbufferARB(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglCreatePbufferARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglCreatePbufferARB,wglCreatePbufferARB(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

HPBUFFEREXT GLAPIENTRY wglCreatePbufferEXT(HDC _p0, int _p1, int _p2, int _p3, const int *_p4)
{
    gli().init();
    HPBUFFEREXT _result;
    PREV_USER_CALL(wglCreatePbufferEXT,wglCreatePbufferEXT(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglCreatePbufferEXT(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglCreatePbufferEXT,wglCreatePbufferEXT(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

void GLAPIENTRY wglDeleteBufferRegionARB(HANDLE _p0)
{
    gli().init();
    PREV_USER_CALL(wglDeleteBufferRegionARB,wglDeleteBufferRegionARB(_p0))
    glCalls().wglDeleteBufferRegionARB(_p0);
    POST_USER_CALL(wglDeleteBufferRegionARB,wglDeleteBufferRegionARB(_p0))
}

int GLAPIENTRY wglDeleteContext(HGLRC _p0)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglDeleteContext,wglDeleteContext(_p0))
    _result = glCalls().wglDeleteContext(_p0);
    POST_USER_CALL(wglDeleteContext,wglDeleteContext(_p0))
    return _result;
}

int GLAPIENTRY wglDescribeLayerPlane(HDC _p0, int _p1, int _p2, unsigned int _p3, LPLAYERPLANEDESCRIPTOR _p4)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglDescribeLayerPlane,wglDescribeLayerPlane(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglDescribeLayerPlane(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglDescribeLayerPlane,wglDescribeLayerPlane(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

int GLAPIENTRY wglDescribePixelFormat(HDC _p0, int _p1, unsigned int _p2, LPPIXELFORMATDESCRIPTOR _p3)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglDescribePixelFormat,wglDescribePixelFormat(_p0,_p1,_p2,_p3))
    _result = glCalls().wglDescribePixelFormat(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglDescribePixelFormat,wglDescribePixelFormat(_p0,_p1,_p2,_p3))
    return _result;
}

void GLAPIENTRY wglDestroyDisplayColorTableEXT(GLushort _p0)
{
    gli().init();
    PREV_USER_CALL(wglDestroyDisplayColorTableEXT,wglDestroyDisplayColorTableEXT(_p0))
    glCalls().wglDestroyDisplayColorTableEXT(_p0);
    POST_USER_CALL(wglDestroyDisplayColorTableEXT,wglDestroyDisplayColorTableEXT(_p0))
}

BOOL GLAPIENTRY wglDestroyImageBufferI3D(HDC _p0, LPVOID _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglDestroyImageBufferI3D,wglDestroyImageBufferI3D(_p0,_p1))
    _result = glCalls().wglDestroyImageBufferI3D(_p0,_p1);
    POST_USER_CALL(wglDestroyImageBufferI3D,wglDestroyImageBufferI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglDestroyPbufferARB(HPBUFFERARB _p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglDestroyPbufferARB,wglDestroyPbufferARB(_p0))
    _result = glCalls().wglDestroyPbufferARB(_p0);
    POST_USER_CALL(wglDestroyPbufferARB,wglDestroyPbufferARB(_p0))
    return _result;
}

BOOL GLAPIENTRY wglDestroyPbufferEXT(HPBUFFEREXT _p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglDestroyPbufferEXT,wglDestroyPbufferEXT(_p0))
    _result = glCalls().wglDestroyPbufferEXT(_p0);
    POST_USER_CALL(wglDestroyPbufferEXT,wglDestroyPbufferEXT(_p0))
    return _result;
}

BOOL GLAPIENTRY wglDisableFrameLockI3D()
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglDisableFrameLockI3D,wglDisableFrameLockI3D())
    _result = glCalls().wglDisableFrameLockI3D();
    POST_USER_CALL(wglDisableFrameLockI3D,wglDisableFrameLockI3D())
    return _result;
}

BOOL GLAPIENTRY wglDisableGenlockI3D(HDC _p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglDisableGenlockI3D,wglDisableGenlockI3D(_p0))
    _result = glCalls().wglDisableGenlockI3D(_p0);
    POST_USER_CALL(wglDisableGenlockI3D,wglDisableGenlockI3D(_p0))
    return _result;
}

BOOL GLAPIENTRY wglEnableFrameLockI3D()
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglEnableFrameLockI3D,wglEnableFrameLockI3D())
    _result = glCalls().wglEnableFrameLockI3D();
    POST_USER_CALL(wglEnableFrameLockI3D,wglEnableFrameLockI3D())
    return _result;
}

BOOL GLAPIENTRY wglEnableGenlockI3D(HDC _p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglEnableGenlockI3D,wglEnableGenlockI3D(_p0))
    _result = glCalls().wglEnableGenlockI3D(_p0);
    POST_USER_CALL(wglEnableGenlockI3D,wglEnableGenlockI3D(_p0))
    return _result;
}

BOOL GLAPIENTRY wglEndFrameTrackingI3D()
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglEndFrameTrackingI3D,wglEndFrameTrackingI3D())
    _result = glCalls().wglEndFrameTrackingI3D();
    POST_USER_CALL(wglEndFrameTrackingI3D,wglEndFrameTrackingI3D())
    return _result;
}

void GLAPIENTRY wglFreeMemoryNV(void *_p0)
{
    gli().init();
    PREV_USER_CALL(wglFreeMemoryNV,wglFreeMemoryNV(_p0))
    glCalls().wglFreeMemoryNV(_p0);
    POST_USER_CALL(wglFreeMemoryNV,wglFreeMemoryNV(_p0))
}

BOOL GLAPIENTRY wglGenlockSampleRateI3D(HDC _p0, UINT _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGenlockSampleRateI3D,wglGenlockSampleRateI3D(_p0,_p1))
    _result = glCalls().wglGenlockSampleRateI3D(_p0,_p1);
    POST_USER_CALL(wglGenlockSampleRateI3D,wglGenlockSampleRateI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGenlockSourceDelayI3D(HDC _p0, UINT _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGenlockSourceDelayI3D,wglGenlockSourceDelayI3D(_p0,_p1))
    _result = glCalls().wglGenlockSourceDelayI3D(_p0,_p1);
    POST_USER_CALL(wglGenlockSourceDelayI3D,wglGenlockSourceDelayI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGenlockSourceEdgeI3D(HDC _p0, UINT _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGenlockSourceEdgeI3D,wglGenlockSourceEdgeI3D(_p0,_p1))
    _result = glCalls().wglGenlockSourceEdgeI3D(_p0,_p1);
    POST_USER_CALL(wglGenlockSourceEdgeI3D,wglGenlockSourceEdgeI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGenlockSourceI3D(HDC _p0, UINT _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGenlockSourceI3D,wglGenlockSourceI3D(_p0,_p1))
    _result = glCalls().wglGenlockSourceI3D(_p0,_p1);
    POST_USER_CALL(wglGenlockSourceI3D,wglGenlockSourceI3D(_p0,_p1))
    return _result;
}

HGLRC GLAPIENTRY wglGetCurrentContext()
{
    gli().init();
    HGLRC _result;
    PREV_USER_CALL(wglGetCurrentContext,wglGetCurrentContext())
    _result = glCalls().wglGetCurrentContext();
    POST_USER_CALL(wglGetCurrentContext,wglGetCurrentContext())
    return _result;
}

HDC GLAPIENTRY wglGetCurrentDC()
{
    gli().init();
    HDC _result;
    PREV_USER_CALL(wglGetCurrentDC,wglGetCurrentDC())
    _result = glCalls().wglGetCurrentDC();
    POST_USER_CALL(wglGetCurrentDC,wglGetCurrentDC())
    return _result;
}

HDC GLAPIENTRY wglGetCurrentReadDCARB()
{
    gli().init();
    HDC _result;
    PREV_USER_CALL(wglGetCurrentReadDCARB,wglGetCurrentReadDCARB())
    _result = glCalls().wglGetCurrentReadDCARB();
    POST_USER_CALL(wglGetCurrentReadDCARB,wglGetCurrentReadDCARB())
    return _result;
}

HDC GLAPIENTRY wglGetCurrentReadDCEXT()
{
    gli().init();
    HDC _result;
    PREV_USER_CALL(wglGetCurrentReadDCEXT,wglGetCurrentReadDCEXT())
    _result = glCalls().wglGetCurrentReadDCEXT();
    POST_USER_CALL(wglGetCurrentReadDCEXT,wglGetCurrentReadDCEXT())
    return _result;
}

BOOL GLAPIENTRY wglGetDigitalVideoParametersI3D(HDC _p0, int _p1, int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetDigitalVideoParametersI3D,wglGetDigitalVideoParametersI3D(_p0,_p1,_p2))
    _result = glCalls().wglGetDigitalVideoParametersI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglGetDigitalVideoParametersI3D,wglGetDigitalVideoParametersI3D(_p0,_p1,_p2))
    return _result;
}

const char * GLAPIENTRY wglGetExtensionsStringARB(HDC _p0)
{
    gli().init();
    const char *_result;
    PREV_USER_CALL(wglGetExtensionsStringARB,wglGetExtensionsStringARB(_p0))
    _result = glCalls().wglGetExtensionsStringARB(_p0);
    POST_USER_CALL(wglGetExtensionsStringARB,wglGetExtensionsStringARB(_p0))
    return _result;
}

const char * GLAPIENTRY wglGetExtensionsStringEXT()
{
    gli().init();
    const char *_result;
    PREV_USER_CALL(wglGetExtensionsStringEXT,wglGetExtensionsStringEXT())
    _result = glCalls().wglGetExtensionsStringEXT();
    POST_USER_CALL(wglGetExtensionsStringEXT,wglGetExtensionsStringEXT())
    return _result;
}

BOOL GLAPIENTRY wglGetFrameUsageI3D(float *_p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetFrameUsageI3D,wglGetFrameUsageI3D(_p0))
    _result = glCalls().wglGetFrameUsageI3D(_p0);
    POST_USER_CALL(wglGetFrameUsageI3D,wglGetFrameUsageI3D(_p0))
    return _result;
}

BOOL GLAPIENTRY wglGetGammaTableI3D(HDC _p0, int _p1, USHORT *_p2, USHORT *_p3, USHORT *_p4)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGammaTableI3D,wglGetGammaTableI3D(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglGetGammaTableI3D(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglGetGammaTableI3D,wglGetGammaTableI3D(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglGetGammaTableParametersI3D(HDC _p0, int _p1, int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGammaTableParametersI3D,wglGetGammaTableParametersI3D(_p0,_p1,_p2))
    _result = glCalls().wglGetGammaTableParametersI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglGetGammaTableParametersI3D,wglGetGammaTableParametersI3D(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglGetGenlockSampleRateI3D(HDC _p0, UINT *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGenlockSampleRateI3D,wglGetGenlockSampleRateI3D(_p0,_p1))
    _result = glCalls().wglGetGenlockSampleRateI3D(_p0,_p1);
    POST_USER_CALL(wglGetGenlockSampleRateI3D,wglGetGenlockSampleRateI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGetGenlockSourceDelayI3D(HDC _p0, UINT *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGenlockSourceDelayI3D,wglGetGenlockSourceDelayI3D(_p0,_p1))
    _result = glCalls().wglGetGenlockSourceDelayI3D(_p0,_p1);
    POST_USER_CALL(wglGetGenlockSourceDelayI3D,wglGetGenlockSourceDelayI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGetGenlockSourceEdgeI3D(HDC _p0, UINT *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGenlockSourceEdgeI3D,wglGetGenlockSourceEdgeI3D(_p0,_p1))
    _result = glCalls().wglGetGenlockSourceEdgeI3D(_p0,_p1);
    POST_USER_CALL(wglGetGenlockSourceEdgeI3D,wglGetGenlockSourceEdgeI3D(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglGetGenlockSourceI3D(HDC _p0, UINT *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetGenlockSourceI3D,wglGetGenlockSourceI3D(_p0,_p1))
    _result = glCalls().wglGetGenlockSourceI3D(_p0,_p1);
    POST_USER_CALL(wglGetGenlockSourceI3D,wglGetGenlockSourceI3D(_p0,_p1))
    return _result;
}

int GLAPIENTRY wglGetLayerPaletteEntries(HDC _p0, int _p1, int _p2, int _p3, COLORREF *_p4)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglGetLayerPaletteEntries,wglGetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglGetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglGetLayerPaletteEntries,wglGetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglGetMscRateOML(HDC _p0, INT32 *_p1, INT32 *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetMscRateOML,wglGetMscRateOML(_p0,_p1,_p2))
    _result = glCalls().wglGetMscRateOML(_p0,_p1,_p2);
    POST_USER_CALL(wglGetMscRateOML,wglGetMscRateOML(_p0,_p1,_p2))
    return _result;
}

HDC GLAPIENTRY wglGetPbufferDCARB(HPBUFFERARB _p0)
{
    gli().init();
    HDC _result;
    PREV_USER_CALL(wglGetPbufferDCARB,wglGetPbufferDCARB(_p0))
    _result = glCalls().wglGetPbufferDCARB(_p0);
    POST_USER_CALL(wglGetPbufferDCARB,wglGetPbufferDCARB(_p0))
    return _result;
}

HDC GLAPIENTRY wglGetPbufferDCEXT(HPBUFFEREXT _p0)
{
    gli().init();
    HDC _result;
    PREV_USER_CALL(wglGetPbufferDCEXT,wglGetPbufferDCEXT(_p0))
    _result = glCalls().wglGetPbufferDCEXT(_p0);
    POST_USER_CALL(wglGetPbufferDCEXT,wglGetPbufferDCEXT(_p0))
    return _result;
}

int GLAPIENTRY wglGetPixelFormat(HDC hdc)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglGetPixelFormat,wglGetPixelFormat(hdc))
    _result = glCalls().wglGetPixelFormat(hdc);
    POST_USER_CALL(wglGetPixelFormat,wglGetPixelFormat(hdc))
    return _result;
}

BOOL GLAPIENTRY wglGetPixelFormatAttribfvARB(HDC _p0, int _p1, int _p2, UINT _p3, const int *_p4, FLOAT *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetPixelFormatAttribfvARB,wglGetPixelFormatAttribfvARB(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglGetPixelFormatAttribfvARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglGetPixelFormatAttribfvARB,wglGetPixelFormatAttribfvARB(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

BOOL GLAPIENTRY wglGetPixelFormatAttribfvEXT(HDC _p0, int _p1, int _p2, UINT _p3, int *_p4, FLOAT *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetPixelFormatAttribfvEXT,wglGetPixelFormatAttribfvEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglGetPixelFormatAttribfvEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglGetPixelFormatAttribfvEXT,wglGetPixelFormatAttribfvEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

BOOL GLAPIENTRY wglGetPixelFormatAttribivARB(HDC _p0, int _p1, int _p2, UINT _p3, const int *_p4, int *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetPixelFormatAttribivARB,wglGetPixelFormatAttribivARB(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglGetPixelFormatAttribivARB(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglGetPixelFormatAttribivARB,wglGetPixelFormatAttribivARB(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

BOOL GLAPIENTRY wglGetPixelFormatAttribivEXT(HDC _p0, int _p1, int _p2, UINT _p3, int *_p4, int *_p5)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetPixelFormatAttribivEXT,wglGetPixelFormatAttribivEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    _result = glCalls().wglGetPixelFormatAttribivEXT(_p0,_p1,_p2,_p3,_p4,_p5);
    POST_USER_CALL(wglGetPixelFormatAttribivEXT,wglGetPixelFormatAttribivEXT(_p0,_p1,_p2,_p3,_p4,_p5))
    return _result;
}

PROC GLAPIENTRY wglGetProcAddress(const char *_p0)
{
    gli().init();
    PROC _result;
    PREV_USER_CALL(wglGetProcAddress,wglGetProcAddress(_p0))
    _result = glCalls().wglGetProcAddress(_p0);
    POST_USER_CALL(wglGetProcAddress,wglGetProcAddress(_p0))
    return _result;
}

int GLAPIENTRY wglGetSwapIntervalEXT()
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglGetSwapIntervalEXT,wglGetSwapIntervalEXT())
    _result = glCalls().wglGetSwapIntervalEXT();
    POST_USER_CALL(wglGetSwapIntervalEXT,wglGetSwapIntervalEXT())
    return _result;
}

BOOL GLAPIENTRY wglGetSyncValuesOML(HDC _p0, INT64 *_p1, INT64 *_p2, INT64 *_p3)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglGetSyncValuesOML,wglGetSyncValuesOML(_p0,_p1,_p2,_p3))
    _result = glCalls().wglGetSyncValuesOML(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglGetSyncValuesOML,wglGetSyncValuesOML(_p0,_p1,_p2,_p3))
    return _result;
}

BOOL GLAPIENTRY wglIsEnabledFrameLockI3D(BOOL *_p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglIsEnabledFrameLockI3D,wglIsEnabledFrameLockI3D(_p0))
    _result = glCalls().wglIsEnabledFrameLockI3D(_p0);
    POST_USER_CALL(wglIsEnabledFrameLockI3D,wglIsEnabledFrameLockI3D(_p0))
    return _result;
}

BOOL GLAPIENTRY wglIsEnabledGenlockI3D(HDC _p0, BOOL *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglIsEnabledGenlockI3D,wglIsEnabledGenlockI3D(_p0,_p1))
    _result = glCalls().wglIsEnabledGenlockI3D(_p0,_p1);
    POST_USER_CALL(wglIsEnabledGenlockI3D,wglIsEnabledGenlockI3D(_p0,_p1))
    return _result;
}

GLboolean GLAPIENTRY wglLoadDisplayColorTableEXT(const GLushort *_p0, GLuint _p1)
{
    gli().init();
    GLboolean _result;
    PREV_USER_CALL(wglLoadDisplayColorTableEXT,wglLoadDisplayColorTableEXT(_p0,_p1))
    _result = glCalls().wglLoadDisplayColorTableEXT(_p0,_p1);
    POST_USER_CALL(wglLoadDisplayColorTableEXT,wglLoadDisplayColorTableEXT(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglMakeContextCurrentARB(HDC _p0, HDC _p1, HGLRC _p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglMakeContextCurrentARB,wglMakeContextCurrentARB(_p0,_p1,_p2))
    _result = glCalls().wglMakeContextCurrentARB(_p0,_p1,_p2);
    POST_USER_CALL(wglMakeContextCurrentARB,wglMakeContextCurrentARB(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglMakeContextCurrentEXT(HDC _p0, HDC _p1, HGLRC _p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglMakeContextCurrentEXT,wglMakeContextCurrentEXT(_p0,_p1,_p2))
    _result = glCalls().wglMakeContextCurrentEXT(_p0,_p1,_p2);
    POST_USER_CALL(wglMakeContextCurrentEXT,wglMakeContextCurrentEXT(_p0,_p1,_p2))
    return _result;
}

int GLAPIENTRY wglMakeCurrent(HDC _p0, HGLRC _p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglMakeCurrent,wglMakeCurrent(_p0,_p1))
    _result = glCalls().wglMakeCurrent(_p0,_p1);
    POST_USER_CALL(wglMakeCurrent,wglMakeCurrent(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglQueryFrameLockMasterI3D(BOOL *_p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglQueryFrameLockMasterI3D,wglQueryFrameLockMasterI3D(_p0))
    _result = glCalls().wglQueryFrameLockMasterI3D(_p0);
    POST_USER_CALL(wglQueryFrameLockMasterI3D,wglQueryFrameLockMasterI3D(_p0))
    return _result;
}

BOOL GLAPIENTRY wglQueryFrameTrackingI3D(DWORD *_p0, DWORD *_p1, float *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglQueryFrameTrackingI3D,wglQueryFrameTrackingI3D(_p0,_p1,_p2))
    _result = glCalls().wglQueryFrameTrackingI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglQueryFrameTrackingI3D,wglQueryFrameTrackingI3D(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglQueryGenlockMaxSourceDelayI3D(HDC _p0, UINT *_p1, UINT *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglQueryGenlockMaxSourceDelayI3D,wglQueryGenlockMaxSourceDelayI3D(_p0,_p1,_p2))
    _result = glCalls().wglQueryGenlockMaxSourceDelayI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglQueryGenlockMaxSourceDelayI3D,wglQueryGenlockMaxSourceDelayI3D(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglQueryPbufferARB(HPBUFFERARB _p0, int _p1, int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglQueryPbufferARB,wglQueryPbufferARB(_p0,_p1,_p2))
    _result = glCalls().wglQueryPbufferARB(_p0,_p1,_p2);
    POST_USER_CALL(wglQueryPbufferARB,wglQueryPbufferARB(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglQueryPbufferEXT(HPBUFFEREXT _p0, int _p1, int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglQueryPbufferEXT,wglQueryPbufferEXT(_p0,_p1,_p2))
    _result = glCalls().wglQueryPbufferEXT(_p0,_p1,_p2);
    POST_USER_CALL(wglQueryPbufferEXT,wglQueryPbufferEXT(_p0,_p1,_p2))
    return _result;
}

int GLAPIENTRY wglRealizeLayerPalette(HDC _p0, int _p1, int _p2)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglRealizeLayerPalette,wglRealizeLayerPalette(_p0,_p1,_p2))
    _result = glCalls().wglRealizeLayerPalette(_p0,_p1,_p2);
    POST_USER_CALL(wglRealizeLayerPalette,wglRealizeLayerPalette(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglReleaseImageBufferEventsI3D(HDC _p0, const LPVOID *_p1, UINT _p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglReleaseImageBufferEventsI3D,wglReleaseImageBufferEventsI3D(_p0,_p1,_p2))
    _result = glCalls().wglReleaseImageBufferEventsI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglReleaseImageBufferEventsI3D,wglReleaseImageBufferEventsI3D(_p0,_p1,_p2))
    return _result;
}

int GLAPIENTRY wglReleasePbufferDCARB(HPBUFFERARB _p0, HDC _p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglReleasePbufferDCARB,wglReleasePbufferDCARB(_p0,_p1))
    _result = glCalls().wglReleasePbufferDCARB(_p0,_p1);
    POST_USER_CALL(wglReleasePbufferDCARB,wglReleasePbufferDCARB(_p0,_p1))
    return _result;
}

int GLAPIENTRY wglReleasePbufferDCEXT(HPBUFFEREXT _p0, HDC _p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglReleasePbufferDCEXT,wglReleasePbufferDCEXT(_p0,_p1))
    _result = glCalls().wglReleasePbufferDCEXT(_p0,_p1);
    POST_USER_CALL(wglReleasePbufferDCEXT,wglReleasePbufferDCEXT(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglReleaseTexImageARB(HPBUFFERARB _p0, int _p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglReleaseTexImageARB,wglReleaseTexImageARB(_p0,_p1))
    _result = glCalls().wglReleaseTexImageARB(_p0,_p1);
    POST_USER_CALL(wglReleaseTexImageARB,wglReleaseTexImageARB(_p0,_p1))
    return _result;
}

BOOL GLAPIENTRY wglRestoreBufferRegionARB(HANDLE _p0, int _p1, int _p2, int _p3, int _p4, int _p5, int _p6)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglRestoreBufferRegionARB,wglRestoreBufferRegionARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    _result = glCalls().wglRestoreBufferRegionARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(wglRestoreBufferRegionARB,wglRestoreBufferRegionARB(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    return _result;
}

BOOL GLAPIENTRY wglSaveBufferRegionARB(HANDLE _p0, int _p1, int _p2, int _p3, int _p4)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSaveBufferRegionARB,wglSaveBufferRegionARB(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglSaveBufferRegionARB(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglSaveBufferRegionARB,wglSaveBufferRegionARB(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglSetDigitalVideoParametersI3D(HDC _p0, int _p1, const int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSetDigitalVideoParametersI3D,wglSetDigitalVideoParametersI3D(_p0,_p1,_p2))
    _result = glCalls().wglSetDigitalVideoParametersI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglSetDigitalVideoParametersI3D,wglSetDigitalVideoParametersI3D(_p0,_p1,_p2))
    return _result;
}

BOOL GLAPIENTRY wglSetGammaTableI3D(HDC _p0, int _p1, const USHORT *_p2, const USHORT *_p3, const USHORT *_p4)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSetGammaTableI3D,wglSetGammaTableI3D(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglSetGammaTableI3D(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglSetGammaTableI3D,wglSetGammaTableI3D(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglSetGammaTableParametersI3D(HDC _p0, int _p1, const int *_p2)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSetGammaTableParametersI3D,wglSetGammaTableParametersI3D(_p0,_p1,_p2))
    _result = glCalls().wglSetGammaTableParametersI3D(_p0,_p1,_p2);
    POST_USER_CALL(wglSetGammaTableParametersI3D,wglSetGammaTableParametersI3D(_p0,_p1,_p2))
    return _result;
}

int GLAPIENTRY wglSetLayerPaletteEntries(HDC _p0, int _p1, int _p2, int _p3, const COLORREF *_p4)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglSetLayerPaletteEntries,wglSetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglSetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglSetLayerPaletteEntries,wglSetLayerPaletteEntries(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

BOOL GLAPIENTRY wglSetPbufferAttribARB(HPBUFFERARB _p0, const int *_p1)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSetPbufferAttribARB,wglSetPbufferAttribARB(_p0,_p1))
    _result = glCalls().wglSetPbufferAttribARB(_p0,_p1);
    POST_USER_CALL(wglSetPbufferAttribARB,wglSetPbufferAttribARB(_p0,_p1))
    return _result;
}

int GLAPIENTRY wglSetPixelFormat(HDC _p0, int _p1, const PIXELFORMATDESCRIPTOR *_p2)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglSetPixelFormat,wglSetPixelFormat(_p0,_p1,_p2))
    _result = glCalls().wglSetPixelFormat(_p0,_p1,_p2);
    POST_USER_CALL(wglSetPixelFormat,wglSetPixelFormat(_p0,_p1,_p2))
    return _result;
}

int GLAPIENTRY wglShareLists(HGLRC _p0, HGLRC _p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglShareLists,wglShareLists(_p0,_p1))
    _result = glCalls().wglShareLists(_p0,_p1);
    POST_USER_CALL(wglShareLists,wglShareLists(_p0,_p1))
    return _result;
}

int GLAPIENTRY wglSwapBuffers(HDC hdc)
{
    gli().init();
    int _result;
    gli().setHDC(hdc);
    if ( gli().isForcedSwap() )
    {
        _result = glCalls().wglSwapBuffers(hdc);
        return _result;
    }
    PREV_USER_CALL(wglSwapBuffers,wglSwapBuffers(hdc))
    _result = glCalls().wglSwapBuffers(hdc);
    POST_USER_CALL(wglSwapBuffers,wglSwapBuffers(hdc))
    gli().doEndFrameEvent();
    return _result;
}

INT64 GLAPIENTRY wglSwapBuffersMscOML(HDC _p0, INT64 _p1, INT64 _p2, INT64 _p3)
{
    gli().init();
    INT64 _result;
    PREV_USER_CALL(wglSwapBuffersMscOML,wglSwapBuffersMscOML(_p0,_p1,_p2,_p3))
    _result = glCalls().wglSwapBuffersMscOML(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglSwapBuffersMscOML,wglSwapBuffersMscOML(_p0,_p1,_p2,_p3))
    return _result;
}

BOOL GLAPIENTRY wglSwapIntervalEXT(int _p0)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglSwapIntervalEXT,wglSwapIntervalEXT(_p0))
    _result = glCalls().wglSwapIntervalEXT(_p0);
    POST_USER_CALL(wglSwapIntervalEXT,wglSwapIntervalEXT(_p0))
    return _result;
}

int GLAPIENTRY wglSwapLayerBuffers(HDC _p0, unsigned int _p1)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglSwapLayerBuffers,wglSwapLayerBuffers(_p0,_p1))
    _result = glCalls().wglSwapLayerBuffers(_p0,_p1);
    POST_USER_CALL(wglSwapLayerBuffers,wglSwapLayerBuffers(_p0,_p1))
    return _result;
}

INT64 GLAPIENTRY wglSwapLayerBuffersMscOML(HDC _p0, int _p1, INT64 _p2, INT64 _p3, INT64 _p4)
{
    gli().init();
    INT64 _result;
    PREV_USER_CALL(wglSwapLayerBuffersMscOML,wglSwapLayerBuffersMscOML(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglSwapLayerBuffersMscOML(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglSwapLayerBuffersMscOML,wglSwapLayerBuffersMscOML(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

int GLAPIENTRY wglUseFontBitmapsA(HDC _p0, unsigned long _p1, unsigned long _p2, unsigned long _p3)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglUseFontBitmapsA,wglUseFontBitmapsA(_p0,_p1,_p2,_p3))
    _result = glCalls().wglUseFontBitmapsA(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglUseFontBitmapsA,wglUseFontBitmapsA(_p0,_p1,_p2,_p3))
    return _result;
}

int GLAPIENTRY wglUseFontBitmapsW(HDC _p0, unsigned long _p1, unsigned long _p2, unsigned long _p3)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglUseFontBitmapsW,wglUseFontBitmapsW(_p0,_p1,_p2,_p3))
    _result = glCalls().wglUseFontBitmapsW(_p0,_p1,_p2,_p3);
    POST_USER_CALL(wglUseFontBitmapsW,wglUseFontBitmapsW(_p0,_p1,_p2,_p3))
    return _result;
}

int GLAPIENTRY wglUseFontOutlinesA(HDC _p0, unsigned long _p1, unsigned long _p2, unsigned long _p3, float _p4, float _p5, int _p6, LPGLYPHMETRICSFLOAT _p7)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglUseFontOutlinesA,wglUseFontOutlinesA(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    _result = glCalls().wglUseFontOutlinesA(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(wglUseFontOutlinesA,wglUseFontOutlinesA(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    return _result;
}

int GLAPIENTRY wglUseFontOutlinesW(HDC _p0, unsigned long _p1, unsigned long _p2, unsigned long _p3, float _p4, float _p5, int _p6, LPGLYPHMETRICSFLOAT _p7)
{
    gli().init();
    int _result;
    PREV_USER_CALL(wglUseFontOutlinesW,wglUseFontOutlinesW(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    _result = glCalls().wglUseFontOutlinesW(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7);
    POST_USER_CALL(wglUseFontOutlinesW,wglUseFontOutlinesW(_p0,_p1,_p2,_p3,_p4,_p5,_p6,_p7))
    return _result;
}

BOOL GLAPIENTRY wglWaitForMscOML(HDC _p0, INT64 _p1, INT64 _p2, INT64 _p3, INT64 *_p4, INT64 *_p5, INT64 *_p6)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglWaitForMscOML,wglWaitForMscOML(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    _result = glCalls().wglWaitForMscOML(_p0,_p1,_p2,_p3,_p4,_p5,_p6);
    POST_USER_CALL(wglWaitForMscOML,wglWaitForMscOML(_p0,_p1,_p2,_p3,_p4,_p5,_p6))
    return _result;
}

BOOL GLAPIENTRY wglWaitForSbcOML(HDC _p0, INT64 _p1, INT64 *_p2, INT64 *_p3, INT64 *_p4)
{
    gli().init();
    BOOL _result;
    PREV_USER_CALL(wglWaitForSbcOML,wglWaitForSbcOML(_p0,_p1,_p2,_p3,_p4))
    _result = glCalls().wglWaitForSbcOML(_p0,_p1,_p2,_p3,_p4);
    POST_USER_CALL(wglWaitForSbcOML,wglWaitForSbcOML(_p0,_p1,_p2,_p3,_p4))
    return _result;
}

