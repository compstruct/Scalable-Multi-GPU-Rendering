/**************************************************************************
 *
 * Copyright (c) 2002 - 2011 by Computer Architecture Department,
 * Universitat Politecnica de Catalunya.
 * All rights reserved.
 *
 * The contents of this file may not be disclosed to third parties,
 * copied or duplicated in any form, in whole or in part, without the
 * prior permission of the authors, Computer Architecture Department
 * and Universitat Politecnica de Catalunya.
 *
 */

#include "ACDXTLFactory.h"
#include <iostream>
#include "support.h"
#include "ImplementedConstantBindingFunctions.h"

using namespace std;
using namespace acdlib;

ACDXTLShader* ACDXTLFactory::tlshader;
ACDXTLState* ACDXTLFactory::tls;
ACDXCodeSnip ACDXTLFactory::code;
ModelviewTransformation ACDXTLFactory::modelview;
ProjectionTransformation ACDXTLFactory::projection;
MVPTransformation ACDXTLFactory::mvp;
bool ACDXTLFactory::computeNormals;
bool ACDXTLFactory::separateModelviewProjection;
bool ACDXTLFactory::computeNHEyePosition;
bool ACDXTLFactory::anyEyeDependantCoordinateGenerationMode;
bool ACDXTLFactory::anyNormalDependantCoordinateGenerationMode;
bool ACDXTLFactory::anyReflectedVectorDependantCoordinateGenerationMode;
ACDXTLState::TextureUnit* ACDXTLFactory::texUnit;
bool ACDXTLFactory::frontFaceCulling;
bool ACDXTLFactory::backFaceCulling;
bool ACDXTLFactory::computeFrontColor;
bool ACDXTLFactory::computeBackColor;
bool ACDXTLFactory::bothFacesCulled;
bool ACDXTLFactory::twoSidedLighting;
bool ACDXTLFactory::separateSpecular;
bool ACDXTLFactory::colorMaterialForEmissionFront;
bool ACDXTLFactory::colorMaterialForEmissionBack;

/* Assembles the program parts created by the different construction functions */
ACDXTLShader* ACDXTLFactory::constructVertexProgram(ACDXTLState& tls)
{
    ACDXTLFactory::tls = &tls;

    constructTLFactoryFlags();

    tlshader = new ACDXTLShader;

    code.clear();

    code.append("!!ARBvp1.0\n");

    constructInitialization();
    constructTransforms();
    constructFogCoordinateOutput();
    constructTextureCoordinate();

    if (ACDXTLFactory::tls->isLighting())
        constructLighting();
    else
        constructNoLighting();    // Bypass input colors to output colors

    code.append("END");

    //code.removeComments();

    destroyTLFactoryFlags();

    tlshader->setCode(code.toString());

    return tlshader; // must be destroyed externally
}

void ACDXTLFactory::constructTLFactoryFlags()
{
    computeNHEyePosition = false;
    separateModelviewProjection = false;
    computeNormals = false;
    anyNormalDependantCoordinateGenerationMode = false;
    anyEyeDependantCoordinateGenerationMode = false;
    anyReflectedVectorDependantCoordinateGenerationMode = false;

    /* Lighting flags */
    twoSidedLighting = tls->twoSidedLighting();
    separateSpecular = tls->separateSpecular();

    /* Derive color computing parameters */

    /* Set Face culling flags */
    frontFaceCulling = (tls->isCullingEnabled() && tls->isFrontFaceCulling());
    backFaceCulling =  (tls->isCullingEnabled() && tls->isBackFaceCulling());

    // If Two-sided lighting enabled then different computation required for back face attributes.
    // If disabled then the computation (front face) is the same for front and back

    computeFrontColor = ( !frontFaceCulling || (!backFaceCulling && frontFaceCulling && !twoSidedLighting) );
    computeBackColor = ( !backFaceCulling && twoSidedLighting );

    bothFacesCulled = frontFaceCulling && backFaceCulling;

    /* Deduce if eye non-homogeneous vertex position is required */
    if (!bothFacesCulled &&
        tls->isLighting() && tls->anyLightEnabled() && (!tls->infiniteViewer() || tls->anyLocalLight()))
        computeNHEyePosition = true;

    /* ACDXTLFactory Space for texture unit related information */
    texUnit = new ACDXTLState::TextureUnit[tls->maxTextureUnits()];

    /* Deduce texture coordinate generation mode requeriments */

    for (int i=0;i < tls->maxTextureUnits(); i++)
    {
        if (tls->isTextureUnitEnabled(i))
        {
            texUnit[i] = tls->getTextureUnit(i);

            if (texUnit[i].activeTexGenS)
            {
                switch(texUnit[i].texGenModeS)
                {
                    case ACDXTLState::TextureUnit::REFLECTION_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::SPHERE_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::NORMAL_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::EYE_LINEAR:
                        anyEyeDependantCoordinateGenerationMode = true;
                        break;
                }
            }
            if (texUnit[i].activeTexGenT)
            {
                switch(texUnit[i].texGenModeT)
                {
                    case ACDXTLState::TextureUnit::REFLECTION_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::SPHERE_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::NORMAL_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::EYE_LINEAR:
                        anyEyeDependantCoordinateGenerationMode = true;
                        break;
                }
            }
            if (texUnit[i].activeTexGenR)
            {
                switch(texUnit[i].texGenModeR)
                {
                    case ACDXTLState::TextureUnit::REFLECTION_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::SPHERE_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::NORMAL_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::EYE_LINEAR:
                        anyEyeDependantCoordinateGenerationMode = true;
                        break;
                }
            }
            if (texUnit[i].activeTexGenQ)
            {
                switch(texUnit[i].texGenModeQ)
                {
                    case ACDXTLState::TextureUnit::REFLECTION_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::SPHERE_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        anyEyeDependantCoordinateGenerationMode = true;
                        anyReflectedVectorDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::NORMAL_MAP:
                        anyNormalDependantCoordinateGenerationMode = true;
                        break;
                    case ACDXTLState::TextureUnit::EYE_LINEAR:
                        anyEyeDependantCoordinateGenerationMode = true;
                        break;
                }
            }
        }
    }

    /* Deduce if separated modelview from projection transformation needed */
    if ((!bothFacesCulled && tls->isLighting() && tls->anyLightEnabled() && (!tls->infiniteViewer() || tls->anyLocalLight())) ||
        anyEyeDependantCoordinateGenerationMode ||
        (tls->fogEnabled() && (tls->fogCoordSrc() == ACDXTLState::FRAGMENT_DEPTH)))
    {
        separateModelviewProjection = true;
    }

    /* Deduce if normal transformation in eye space and normalization required */
    if ((!bothFacesCulled && (tls->isLighting() && tls->anyLightEnabled())) ||
        anyNormalDependantCoordinateGenerationMode)
        computeNormals = true;

    colorMaterialForEmissionFront = (tls->colorMaterialFrontEnabled() && (tls->colorMaterialMode() == ACDXTLState::EMISSION));
    colorMaterialForEmissionBack = (tls->colorMaterialBackEnabled() && (tls->colorMaterialMode() == ACDXTLState::EMISSION));
}

void ACDXTLFactory::destroyTLFactoryFlags()
{
    delete[] texUnit;
}

/* Constructs the parameter initialization part of the vertex program */
void ACDXTLFactory::constructInitialization()
{
    /* binding of input variables :
     *  - position (always)
     *    - color primary i/o secondary (if not lighting)
     *    - normal (if lighting and any light enabled or if normal dependant
     *              coordinate generation mode (Sphere_map, Reflection_map or
     *              Normal_map modes))
     */

    code.append(BasicInputInit(tls->isLighting(),tls->anyLightEnabled(), computeNormals,
                               separateSpecular, computeFrontColor, computeBackColor, tls->isRescaling(),
                               ( tls->colorMaterialFrontEnabled() && (tls->colorMaterialMode() == ACDXTLState::EMISSION) ),
                                 ( tls->colorMaterialBackEnabled() && (tls->colorMaterialMode() == ACDXTLState::EMISSION) )));

    if ( tls->isRescaling() )
    {
        std::vector<ACDX_STORED_FP_ITEM_ID> vState;
        vState.push_back(ACDX_M_MODELVIEW);

        ACDXConstantBinding* cb = ACDXCreateConstantBinding(ACDX_BINDING_TARGET_LOCAL, 
                                                            40, vState, 
                                                            new ScaleFactorFunction);
        tlshader->addConstantBinding(cb);
        //tlshader->addLocal(new ScaleFactor);
    }

    /* initialize matrices (modelview, transposeinverse modelview, projection) */

    code.append(MatricesInit(separateModelviewProjection,computeNormals));

    if ( tls->isLighting() && tls->anyLightEnabled()) /* lighting is enabled */
    {
        int i;
        code.append("# ------------- Lights Initialization -------------------\n");
        for (i=0; i<tls->maxLights(); i++) /* each light source */
        {
            if ( tls->isLightEnabled(i) ) /* light enabled */
            {

                /* initialize lightparameters:
                      - position
                      - ambient/diffuse/specular color/material product
                */
                code.append(LightInit(i, tls->infiniteViewer(),
                            tls->localLightSource(i), tls->isSpotLight(i)));

                if ( !tls->localLightSource(i) )
                {
                    std::vector<ACDX_STORED_FP_ITEM_ID> vState;
                    vState.push_back(ACDX_STORED_FP_ITEM_ID(ACDX_LIGHT_DIRECTION + i * ACDX_LIGHT_PROPERTIES_COUNT));

                    ACDXConstantBinding* cb = ACDXCreateConstantBinding(ACDX_BINDING_TARGET_LOCAL, 
                                                                        i, vState, 
                                                                        new LightPosNormalizeFunction);
                    tlshader->addConstantBinding(cb);
                    //tlshader->addLocal(new LightPosNormalization(i));
                }
            }
        }
        code.append("# ------------ End Lights Initialization ----------------\n");
    }

    /* initialize temporary variables */

    vector<bool> textureUnitEnabled(tls->maxTextureUnits());
    vector<bool> texCoordMultiplicationRequired(tls->maxTextureUnits());

    for (int i=0; i<tls->maxTextureUnits(); i++)
    {
        if (tls->isTextureUnitEnabled(i))
        {
            textureUnitEnabled[i] = true;

            if (texUnit[i].textureMatrixIsIdentity)
                texCoordMultiplicationRequired[i] = false;
            else
                texCoordMultiplicationRequired[i] = true;
        }
        else
        {
            textureUnitEnabled[i] = false;
            texCoordMultiplicationRequired[i] = false;
        }
    }

    code.append(TemporaryInit(tls->isLighting(),tls->anyLightEnabled(), separateSpecular,
                              computeFrontColor, computeBackColor,
                              tls->anyLocalLight(), tls->infiniteViewer(),
                              tls->fogEnabled(),
                              separateModelviewProjection, computeNormals,
                              textureUnitEnabled,
                              texCoordMultiplicationRequired));

    /* initialize output variables:
          - position
          - color: primary front, primary back, secondary front i/o secondary back
    */

    code.append(OutputInit(separateSpecular, twoSidedLighting));

}



void ACDXTLFactory::constructModelviewTransform()
{
    /* Multiply the vertex position with the modelview matrix */
    code.append(modelview);
}

void ACDXTLFactory::constructMVPTransform()
{
    /* Multiply the vertex position with the modelview projection matrix */
    code.append(mvp);
}

void ACDXTLFactory::constructNormalTransform()
{
    /* Multiply the vertex normal with the inverse transposed of the modelview matrix. */
    code.append(NormalTransformation(tls->normalizeNormals(), tls->isRescaling()));
}

void ACDXTLFactory::constructNHEyePositionTransform()
{
    /* Divide Eye vertex position by w component */
    code.append(NHEyePositionComputing());
}

void ACDXTLFactory::constructProjectionTransform()
{
    /* Multiply the vertex with the projection matrix. */
    code.append(projection);
}

/* Constructs the transformation part of the vertex program */
void ACDXTLFactory::constructTransforms()
{
    code.append("# ------------ Vertex position transformations -----------\n");

    if (separateModelviewProjection)
    {
        constructModelviewTransform();
        constructProjectionTransform();
    }
    else
    {
        constructMVPTransform();
    }

    if (computeNormals)
    {
        constructNormalTransform();
    }

    if (computeNHEyePosition)
    {
        constructNHEyePositionTransform();
    }

    code.append("# ------------ End Vertex position transformations -----------\n");
}

void ACDXTLFactory::computeVertexEyeVector()
{
    /* Calculates the VPe vector and normalizes it. */
    code.append(VertexEyeVectorComputing());
}

void ACDXTLFactory::computeAttenuation(Light i)
{
    /* Calculate the vertex to light position */
    /* Calculate the attenuation of the light source. */
    code.append(AttenuationComputing(i));
}

void ACDXTLFactory::computeSpotlight(Light i )
{
    code.append(SpotLightComputation(i));
    /* Calculate the spotlight of the light source. */
    /* Multiply the result with the attenuation */
}


void ACDXTLFactory::computeDiffuseAndSpecularComponents(Light i, bool locallight, bool computeFront, bool computeBack, bool localviewer)
{
    code.append(DifusseAndSpecularComputing(i, locallight, computeFront, computeBack, localviewer));
}

void ACDXTLFactory::computeHalfVector(Light i, bool locallight, bool localviewer)
{
    code.append(HalfVectorComputing(i,locallight,!localviewer));
}

void ACDXTLFactory::computePrimaryColor(Light i, bool computeFront, bool computeBack, bool separate_specular)
{
    code.append(PrimaryColorComputing(i, computeFront, computeBack, separate_specular));
}

void ACDXTLFactory::computeSecondaryColor(Light i, bool computeFront, bool computeBack)
{
    code.append(SecondaryColorComputing(i, computeFront, computeBack));
}

void ACDXTLFactory::computeSceneColor(bool computeFront, bool computeBack, bool separateSpecular,bool colorMaterialEmissionFront, bool colorMaterialEmissionBack)
{
    code.append(SceneColorComputing(computeFront, computeBack, separateSpecular, colorMaterialEmissionFront, colorMaterialEmissionBack));
}



void ACDXTLFactory::constructTextureCoordinate()
{
    constructTextureCoordinateOutput();
    constructTextureCoordinateTransform();
}

void ACDXTLFactory::constructTextureCoordinateOutput()
{
    if ( tls->anyTextureUnitEnabled() )
    {
        code.append("# --------- Texture coordinates output --------\n");

        if (anyReflectedVectorDependantCoordinateGenerationMode)
        {
            code.append("TEMP reflectedVector;\n");
            code.append(NormalizeVector("eyePos"));
            code.append(ReflectedVectorComputing());
        }

        /* We track automatic coordinate generation for each texture unit
         * and each coordinate of texture unit. This prevents to repeat
         * computations (for example: reflected vector computation) between
         * diferents coordinates in the same unit or in diferent texture units
         * that could be applied only once per-vertex.
         */
        vector<string> coordinatesForObjectLinear(tls->maxTextureUnits());
        vector<string> coordinatesForEyeLinear(tls->maxTextureUnits());
        vector<string> coordinatesForSphereMap(tls->maxTextureUnits());
        vector<string> coordinatesForReflectionMap(tls->maxTextureUnits());
        vector<string> coordinatesForNormalMap(tls->maxTextureUnits());

        bool anyObjectLinear = false;
        bool anyEyeLinear = false;
        bool anySphereMap = false;
        bool anyReflectionMap = false;
        bool anyNormalMap = false;

        for ( int i = 0; i < tls->maxTextureUnits(); i++ )
        {
            coordinatesForObjectLinear[i] = "";
            coordinatesForEyeLinear[i] = "";
            coordinatesForSphereMap[i] = "";
            coordinatesForReflectionMap[i] = "";
            coordinatesForNormalMap[i] = "";

            if ( tls->isTextureUnitEnabled(i) )
            {
                // Analize texture generation modes of texture coordinates

                if (texUnit[i].activeTexGenS)
                {
                    switch(texUnit[i].texGenModeS)
                    {
                        case ACDXTLState::TextureUnit::OBJECT_LINEAR:    coordinatesForObjectLinear[i] += "s";  anyObjectLinear = true;  break;
                        case ACDXTLState::TextureUnit::EYE_LINEAR:        coordinatesForEyeLinear[i] += "s";        anyEyeLinear = true;     break;
                        case ACDXTLState::TextureUnit::SPHERE_MAP:        coordinatesForSphereMap[i] += "s";        anySphereMap = true;     break;
                        case ACDXTLState::TextureUnit::REFLECTION_MAP:    coordinatesForReflectionMap[i] += "s"; anyReflectionMap = true; break;
                        case ACDXTLState::TextureUnit::NORMAL_MAP:        coordinatesForNormalMap[i] += "s";     anyNormalMap = true;     break;
                        default:
                            panic("ACDXTLFactory","constructTextureCoordinateGeneration","Unexpected texture generation mode for coordinate s");
                    }
                }

                if (texUnit[i].activeTexGenT)
                {
                    switch(texUnit[i].texGenModeT)
                    {
                        case ACDXTLState::TextureUnit::OBJECT_LINEAR:    coordinatesForObjectLinear[i] += "t";  anyObjectLinear = true;  break;
                        case ACDXTLState::TextureUnit::EYE_LINEAR:        coordinatesForEyeLinear[i] += "t";     anyEyeLinear = true;     break;
                        case ACDXTLState::TextureUnit::SPHERE_MAP:        coordinatesForSphereMap[i] += "t";     anySphereMap = true;     break;
                        case ACDXTLState::TextureUnit::REFLECTION_MAP:    coordinatesForReflectionMap[i] += "t"; anyReflectionMap = true; break;
                        case ACDXTLState::TextureUnit::NORMAL_MAP:        coordinatesForNormalMap[i] += "t";     anyNormalMap = true;     break;
                        default:
                            panic("ACDXTLFactory","constructTextureCoordinateGeneration","Unexpected texture generation mode for coordinate t");
                    }
                }

                if (texUnit[i].activeTexGenR)
                {
                    switch(texUnit[i].texGenModeR)
                    {
                        case ACDXTLState::TextureUnit::OBJECT_LINEAR:    coordinatesForObjectLinear[i] += "r";  anyObjectLinear = true;  break;
                        case ACDXTLState::TextureUnit::EYE_LINEAR:        coordinatesForEyeLinear[i] += "r";     anyEyeLinear = true;     break;
                        case ACDXTLState::TextureUnit::SPHERE_MAP:        coordinatesForSphereMap[i] += "r";     anySphereMap = true;     break;
                        case ACDXTLState::TextureUnit::REFLECTION_MAP:    coordinatesForReflectionMap[i] += "r"; anyReflectionMap = true; break;
                        case ACDXTLState::TextureUnit::NORMAL_MAP:        coordinatesForNormalMap[i] += "r";     anyNormalMap = true;     break;
                        default:
                            panic("ACDXTLFactory","constructTextureCoordinateGeneration","Unexpected texture generation mode for coordinate r");
                    }
                }

                if (texUnit[i].activeTexGenQ)
                {
                    switch(texUnit[i].texGenModeQ)
                    {
                        case ACDXTLState::TextureUnit::OBJECT_LINEAR:    coordinatesForObjectLinear[i] += "q";  anyObjectLinear = true;  break;
                        case ACDXTLState::TextureUnit::EYE_LINEAR:        coordinatesForEyeLinear[i] += "q";     anyEyeLinear = true;     break;
                        case ACDXTLState::TextureUnit::SPHERE_MAP:        coordinatesForSphereMap[i] += "q";     anySphereMap = true;     break;
                        case ACDXTLState::TextureUnit::REFLECTION_MAP:    coordinatesForReflectionMap[i] += "q"; anyReflectionMap = true; break;
                        case ACDXTLState::TextureUnit::NORMAL_MAP:        coordinatesForNormalMap[i] += "q";     anyNormalMap = true;     break;
                        default:
                            panic("ACDXTLFactory","constructTextureCoordinateGeneration","Unexpected texture generation mode for coordinate q");
                    }
                }

                if (!texUnit[i].activeTexGenS && !texUnit[i].activeTexGenT && !texUnit[i].activeTexGenR && !texUnit[i].activeTexGenQ)
                /* If automatic texture coordinate generation is disabled.
                 * Manual texture coordinate bypass.
                 */
                    code.append(TextureBypass(i));

            }
        }

        if (anyObjectLinear)
            code.append(ObjectLinearGeneration(tls->maxTextureUnits(),coordinatesForObjectLinear));

        if (anyEyeLinear)
            code.append(EyeLinearGeneration(tls->maxTextureUnits(),coordinatesForEyeLinear));

        if (anySphereMap)
            code.append(SphereMapGeneration(tls->maxTextureUnits(),coordinatesForSphereMap));

        if (anyReflectionMap)
            code.append(ReflectionMapGeneration(tls->maxTextureUnits(),coordinatesForReflectionMap));

        if (anyNormalMap)
            code.append(NormalMapGeneration(tls->maxTextureUnits(),coordinatesForNormalMap));

    }

}

void ACDXTLFactory::constructTextureCoordinateTransform()
{
    if ( tls->anyTextureUnitEnabled() )
    {
        for ( int i = 0; i < tls->maxTextureUnits(); i++ )
        {
            if ( tls->isTextureUnitEnabled(i) )
            {
                if (!texUnit[i].textureMatrixIsIdentity)
                    code.append(TextureMatrixTransformation(i));
            }
        }
    }

}

void ACDXTLFactory::constructNoLighting()
{
    code.append("# Final output color copy \n");

    if (!bothFacesCulled)
    {
        // Move primary input color to primary output color
        code.append("MOV oColorPrimFront, iColorPrim;\n");

        if (twoSidedLighting)
        {
            // For back face
            code.append("MOV oColorPrimBack, iColorPrim;\n");
        }

        if ( separateSpecular ) /* separate specular color is enabled */
        {
            /* move secondary input color to secondary input color. */
            code.append("MOV oColorSecFront, iColorSec;\n");

            if (twoSidedLighting)
            {
                // For back face
                code.append("MOV oColorSecBack, iColorSec;\n");
            }
        }

    }
    else
        // Needed for primitive assembly stage. At least two vertex attributes must be written in case
        // of GL_FRONT_AND_BACK face culling.
        code.append("MOV result.color.front.primary, {0,0,0,0};\n");

}


void ACDXTLFactory::constructLighting()
{
    if (!bothFacesCulled)
    {
        code.append("# ------------ Lighting calculations -----------\n");

        if (tls->anyLightEnabled() && !tls->infiniteViewer())
            computeVertexEyeVector();

        int i;

        for (i=0; i<tls->maxLights(); i++) /* each light source */
        {
            if ( tls->isLightEnabled(i) ) /* light enabled */
            {
                if ( tls->localLightSource(i) ) /* light source is local */
                {
                    computeAttenuation(i);

                    if ( tls->isSpotLight(i) ) /* light source is spotlight */
                    {
                        computeSpotlight(i);
                    }
                    if ( !tls->infiniteViewer() ) /* viewer is local */
                    {
                        computeHalfVector(i,true,true);
                        computeDiffuseAndSpecularComponents(i, true, computeFrontColor, false, true);
                    }
                    else
                    {
                        computeHalfVector(i,true,false);
                        computeDiffuseAndSpecularComponents(i, true, computeFrontColor, false, false);
                    }
                    if ( separateSpecular ) /* primary and secondary color is used */
                    {
                        computePrimaryColor(i, computeFrontColor, false, true);
                        computeSecondaryColor(i, computeFrontColor, false);
                    }
                    else
                    { /* primary and secondary color is put together */
                        computePrimaryColor(i, computeFrontColor, false, false);
                    }

                    if ( twoSidedLighting ) /* two sided lighting is used */
                    {
                        if ( !tls->infiniteViewer() ) /* viewer is local */
                        {
                            computeHalfVector(i,true,true);
                            computeDiffuseAndSpecularComponents(i, true, false, computeBackColor, true);
                        }
                        else
                        {
                            computeHalfVector(i,true,false);
                            computeDiffuseAndSpecularComponents(i, true, false, computeBackColor, false);
                        }

                        if ( separateSpecular ) /* primary and secondary color is used */
                        {
                            computePrimaryColor(i, false, computeBackColor, true);
                            computeSecondaryColor(i, false, computeBackColor);
                        }
                        else
                        { /* primary and secondary color is put together */
                            computePrimaryColor(i, false, computeBackColor, false);
                        }
                    }
                }
                else // light source is infinite
                {
                    if ( !tls->infiniteViewer() ) /* viewer is local */
                    {
                           computeHalfVector(i,false,true);
                        computeDiffuseAndSpecularComponents(i, false, computeFrontColor, false, true);
                    }
                    else
                    {
                           computeHalfVector(i,false,false);
                        computeDiffuseAndSpecularComponents(i, false, computeFrontColor, false, false);
                    }
                    if ( separateSpecular ) /* primary and secondary color is used */
                    {
                        computePrimaryColor(i, computeFrontColor, false, true);
                        computeSecondaryColor(i, computeFrontColor, false);
                    }
                    else
                    { /* primary and secondary color is put together */
                        computePrimaryColor(i, computeFrontColor, false, false);
                    }

                    if ( twoSidedLighting ) /* two sided lighting is used */
                    {
                        if ( !tls->infiniteViewer() ) /* viewer is local */
                        {
                               computeHalfVector(i,false,true);
                            computeDiffuseAndSpecularComponents(i, false, false, computeBackColor, true);
                        }
                        else
                        {
                               computeHalfVector(i,false,false);
                            computeDiffuseAndSpecularComponents(i, false, false, computeBackColor, false);
                        }
                        if ( separateSpecular ) /* primary and secondary color is used */
                        {
                            computePrimaryColor(i, false, computeBackColor, true);
                            computeSecondaryColor(i, false, computeBackColor);
                        }
                        else
                        { /* primary and secondary color is put together */
                            computePrimaryColor(i, false, computeBackColor, false);
                        }
                    }

                } /* end: light source is infinite */
            } /* end: light enabled */
        } /* end: for-loop */

        /* Scene color */
        computeSceneColor(computeFrontColor, computeBackColor, separateSpecular,
                          colorMaterialForEmissionFront, colorMaterialForEmissionBack);

        code.append("# ------------ End Lighting calculations -----------\n");
    }
    else // both faces culled
        // Needed for primitive assembly stage. At least two vertex attributes must be written in case
        // of GL_FRONT_AND_BACK face culling.
        code.append("MOV result.color.front.primary, {0,0,0,0};\n");

}



void ACDXTLFactory::constructFogCoordinateOutput()
{
    if (tls->fogEnabled())
    {
        code.append("# ------------ Fog coordinate computing -----------\n");
        if (tls->fogCoordSrc() == ACDXTLState::FRAGMENT_DEPTH)
        {
            code.append("ABS result.fogcoord.x, eyePos.z;\n");
        }
        else if (tls->fogCoordSrc() == ACDXTLState::FOG_COORD)
        {
            code.append("MOV result.fogcoord.x, vertex.fogcoord.x;\n");
        }
        code.append("# ---------- End fog coordinate computing ---------\n");
    }
}
