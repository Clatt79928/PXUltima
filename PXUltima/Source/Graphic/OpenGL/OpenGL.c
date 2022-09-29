#include "OpenGL.h"

// wingdi.h
#include <stdio.h>

#include <Error/ActionResult.h>
#include <Memory/Memory.h>
#include <Text/Text.h>
#include <Container/ClusterValue.h>
#include <OS/PXWindow.h>

#if OSUnix
#pragma comment(lib, "opengl32.so")
#elif OSWindows
#pragma comment(lib, "opengl32.lib")
#endif

//---<Version 1.3>------------------
#define GL_MULTISAMPLE 0x809D
#define GL_SAMPLE_ALPHA_TO_COVERAGE 0x809E
#define GL_SAMPLE_ALPHA_TO_ONE 0x809F
#define GL_SAMPLE_COVERAGE 0x80A0
#define GL_SAMPLE_BUFFERS 0x80A8
#define GL_SAMPLES 0x80A9
#define GL_SAMPLE_COVERAGE_VALUE 0x80AA
#define GL_SAMPLE_COVERAGE_INVERT 0x80AB
#define GL_CLAMP_TO_BORDER 0x812D
#define GL_TEXTURE0 0x84C0
#define GL_TEXTURE1 0x84C1
#define GL_TEXTURE2 0x84C2
#define GL_TEXTURE3 0x84C3
#define GL_TEXTURE4 0x84C4
#define GL_TEXTURE5 0x84C5
#define GL_TEXTURE6 0x84C6
#define GL_TEXTURE7 0x84C7
#define GL_TEXTURE8 0x84C8
#define GL_TEXTURE9 0x84C9
#define GL_TEXTURE10 0x84CA
#define GL_TEXTURE11 0x84CB
#define GL_TEXTURE12 0x84CC
#define GL_TEXTURE13 0x84CD
#define GL_TEXTURE14 0x84CE
#define GL_TEXTURE15 0x84CF
#define GL_TEXTURE16 0x84D0
#define GL_TEXTURE17 0x84D1
#define GL_TEXTURE18 0x84D2
#define GL_TEXTURE19 0x84D3
#define GL_TEXTURE20 0x84D4
#define GL_TEXTURE21 0x84D5
#define GL_TEXTURE22 0x84D6
#define GL_TEXTURE23 0x84D7
#define GL_TEXTURE24 0x84D8
#define GL_TEXTURE25 0x84D9
#define GL_TEXTURE26 0x84DA
#define GL_TEXTURE27 0x84DB
#define GL_TEXTURE28 0x84DC
#define GL_TEXTURE29 0x84DD
#define GL_TEXTURE30 0x84DE
#define GL_TEXTURE31 0x84DF
#define GL_ACTIVE_TEXTURE 0x84E0
#define GL_CLIENT_ACTIVE_TEXTURE 0x84E1
#define GL_MAX_TEXTURE_UNITS 0x84E2
#define GL_TRANSPOSE_MODELVIEW_MATRIX 0x84E3
#define GL_TRANSPOSE_PROJECTION_MATRIX 0x84E4
#define GL_TRANSPOSE_TEXTURE_MATRIX 0x84E5
#define GL_TRANSPOSE_COLOR_MATRIX 0x84E6
#define GL_SUBTRACT 0x84E7
#define GL_COMPRESSED_ALPHA 0x84E9
#define GL_COMPRESSED_LUMINANCE 0x84EA
#define GL_COMPRESSED_LUMINANCE_ALPHA 0x84EB
#define GL_COMPRESSED_INTENSITY 0x84EC
#define GL_COMPRESSED_RGB 0x84ED
#define GL_COMPRESSED_RGBA 0x84EE
#define GL_TEXTURE_COMPRESSION_HINT 0x84EF
#define GL_NORMAL_MAP 0x8511
#define GL_REFLECTION_MAP 0x8512
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_BINDING_CUBE_MAP 0x8514
#define GL_TEXTURE_CUBE_MAP_POSITIVE_X 0x8515
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_X 0x8516
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Y 0x8517
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Y 0x8518
#define GL_TEXTURE_CUBE_MAP_POSITIVE_Z 0x8519
#define GL_TEXTURE_CUBE_MAP_NEGATIVE_Z 0x851A
#define GL_PROXY_TEXTURE_CUBE_MAP 0x851B
#define GL_MAX_CUBE_MAP_TEXTURE_SIZE 0x851C
#define GL_COMBINE 0x8570
#define GL_COMBINE_RGB 0x8571
#define GL_COMBINE_ALPHA 0x8572
#define GL_RGB_SCALE 0x8573
#define GL_ADD_SIGNED 0x8574
#define GL_INTERPOLATE 0x8575
#define GL_CONSTANT 0x8576
#define GL_PRIMARY_COLOR 0x8577
#define GL_PREVIOUS 0x8578
#define GL_SOURCE0_RGB 0x8580
#define GL_SOURCE1_RGB 0x8581
#define GL_SOURCE2_RGB 0x8582
#define GL_SOURCE0_ALPHA 0x8588
#define GL_SOURCE1_ALPHA 0x8589
#define GL_SOURCE2_ALPHA 0x858A
#define GL_OPERAND0_RGB 0x8590
#define GL_OPERAND1_RGB 0x8591
#define GL_OPERAND2_RGB 0x8592
#define GL_OPERAND0_ALPHA 0x8598
#define GL_OPERAND1_ALPHA 0x8599
#define GL_OPERAND2_ALPHA 0x859A
#define GL_TEXTURE_COMPRESSED_IMAGE_SIZE 0x86A0
#define GL_TEXTURE_COMPRESSED 0x86A1
#define GL_NUM_COMPRESSED_TEXTURE_FORMATS 0x86A2
#define GL_COMPRESSED_TEXTURE_FORMATS 0x86A3
#define GL_DOT3_RGB 0x86AE
#define GL_DOT3_RGBA 0x86AF
#define GL_MULTISAMPLE_BIT 0x20000000
//----------------------------------



//---------------------------------- Version 2
#define GL_BLEND_EQUATION_RGB GL_BLEND_EQUATION
#define GL_VERTEX_ATTRIB_ARRAY_ENABLED 0x8622
#define GL_VERTEX_ATTRIB_ARRAY_SIZE 0x8623
#define GL_VERTEX_ATTRIB_ARRAY_STRIDE 0x8624
#define GL_VERTEX_ATTRIB_ARRAY_TYPE 0x8625
#define GL_CURRENT_VERTEX_ATTRIB 0x8626
#define GL_VERTEX_PROGRAM_POINT_SIZE 0x8642
#define GL_VERTEX_PROGRAM_TWO_SIDE 0x8643
#define GL_VERTEX_ATTRIB_ARRAY_POINTER 0x8645
#define GL_STENCIL_BACK_FUNC 0x8800
#define GL_STENCIL_BACK_FAIL 0x8801
#define GL_STENCIL_BACK_PASS_DEPTH_FAIL 0x8802
#define GL_STENCIL_BACK_PASS_DEPTH_PASS 0x8803
#define GL_MAX_DRAW_BUFFERS 0x8824
#define GL_DRAW_BUFFER0 0x8825
#define GL_DRAW_BUFFER1 0x8826
#define GL_DRAW_BUFFER2 0x8827
#define GL_DRAW_BUFFER3 0x8828
#define GL_DRAW_BUFFER4 0x8829
#define GL_DRAW_BUFFER5 0x882A
#define GL_DRAW_BUFFER6 0x882B
#define GL_DRAW_BUFFER7 0x882C
#define GL_DRAW_BUFFER8 0x882D
#define GL_DRAW_BUFFER9 0x882E
#define GL_DRAW_BUFFER10 0x882F
#define GL_DRAW_BUFFER11 0x8830
#define GL_DRAW_BUFFER12 0x8831
#define GL_DRAW_BUFFER13 0x8832
#define GL_DRAW_BUFFER14 0x8833
#define GL_DRAW_BUFFER15 0x8834
#define GL_BLEND_EQUATION_ALPHA 0x883D
#define GL_POINT_SPRITE 0x8861
#define GL_COORD_REPLACE 0x8862
#define GL_MAX_VERTEX_ATTRIBS 0x8869
#define GL_VERTEX_ATTRIB_ARRAY_NORMALIZED 0x886A
#define GL_MAX_TEXTURE_COORDS 0x8871
#define GL_MAX_TEXTURE_IMAGE_UNITS 0x8872
#define GL_FRAGMENT_SHADER 0x8B30
#define GL_VERTEX_SHADER 0x8B31
#define GL_MAX_FRAGMENT_UNIFORM_COMPONENTS 0x8B49
#define GL_MAX_VERTEX_UNIFORM_COMPONENTS 0x8B4A
#define GL_MAX_VARYING_FLOATS 0x8B4B
#define GL_MAX_VERTEX_TEXTURE_IMAGE_UNITS 0x8B4C
#define GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS 0x8B4D
#define GL_SHADER_TYPE 0x8B4F
#define GL_FLOAT_VEC2 0x8B50
#define GL_FLOAT_VEC3 0x8B51
#define GL_FLOAT_VEC4 0x8B52
#define GL_INT_VEC2 0x8B53
#define GL_INT_VEC3 0x8B54
#define GL_INT_VEC4 0x8B55
#define GL_BOOL 0x8B56
#define GL_BOOL_VEC2 0x8B57
#define GL_BOOL_VEC3 0x8B58
#define GL_BOOL_VEC4 0x8B59
#define GL_FLOAT_MAT2 0x8B5A
#define GL_FLOAT_MAT3 0x8B5B
#define GL_FLOAT_MAT4 0x8B5C
#define GL_SAMPLER_1D 0x8B5D
#define GL_SAMPLER_2D 0x8B5E
#define GL_SAMPLER_3D 0x8B5F
#define GL_SAMPLER_CUBE 0x8B60
#define GL_SAMPLER_1D_SHADOW 0x8B61
#define GL_SAMPLER_2D_SHADOW 0x8B62
#define GL_DELETE_STATUS 0x8B80
#define GL_COMPILE_STATUS 0x8B81
#define GL_LINK_STATUS 0x8B82
#define GL_VALIDATE_STATUS 0x8B83
#define GL_INFO_LOG_LENGTH 0x8B84
#define GL_ATTACHED_SHADERS 0x8B85
#define GL_ACTIVE_UNIFORMS 0x8B86
#define GL_ACTIVE_UNIFORM_MAX_LENGTH 0x8B87
#define GL_SHADER_SOURCE_LENGTH 0x8B88
#define GL_ACTIVE_ATTRIBUTES 0x8B89
#define GL_ACTIVE_ATTRIBUTE_MAX_LENGTH 0x8B8A
#define GL_FRAGMENT_SHADER_DERIVATIVE_HINT 0x8B8B
#define GL_SHADING_LANGUAGE_VERSION 0x8B8C
#define GL_CURRENT_PROGRAM 0x8B8D
#define GL_POINT_SPRITE_COORD_ORIGIN 0x8CA0
#define GL_LOWER_LEFT 0x8CA1
#define GL_UPPER_LEFT 0x8CA2
#define GL_STENCIL_BACK_REF 0x8CA3
#define GL_STENCIL_BACK_VALUE_MASK 0x8CA4
#define GL_STENCIL_BACK_WRITEMASK 0x8CA5
//----------------------------------


// extension sparse

#define GL_TEXTURE_2D 0x0DE1
#define GL_TEXTURE_3D 0x806F
#define GL_TEXTURE_CUBE_MAP 0x8513
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_TEXTURE_CUBE_MAP_ARRAY_OES 0x9009
#define GL_VIRTUAL_PAGE_SIZE_X_EXT 0x9195
#define GL_VIRTUAL_PAGE_SIZE_Y_EXT 0x9196
#define GL_VIRTUAL_PAGE_SIZE_Z_EXT 0x9197
#define GL_MAX_SPARSE_TEXTURE_SIZE_EXT 0x9198
#define GL_MAX_SPARSE_3D_TEXTURE_SIZE_EXT 0x9199
#define GL_MAX_SPARSE_ARRAY_TEXTURE_LAYERS_EXT 0x919A
#define GL_TEXTURE_SPARSE_EXT 0x91A6
#define GL_VIRTUAL_PAGE_SIZE_INDEX_EXT 0x91A7
#define GL_NUM_VIRTUAL_PAGE_SIZES_EXT 0x91A8
#define GL_SPARSE_TEXTURE_FULL_ARRAY_CUBE_MIPMAPS_EXT 0x91A9
#define GL_NUM_SPARSE_LEVELS_EXT 0x91AA


// extension framebuffer
#define GL_INVALID_FRAMEBUFFER_OPERATION 0x0506
#define GL_FRAMEBUFFER_ATTACHMENT_COLOR_ENCODING 0x8210
#define GL_FRAMEBUFFER_ATTACHMENT_COMPONENT_TYPE 0x8211
#define GL_FRAMEBUFFER_ATTACHMENT_RED_SIZE 0x8212
#define GL_FRAMEBUFFER_ATTACHMENT_GREEN_SIZE 0x8213
#define GL_FRAMEBUFFER_ATTACHMENT_BLUE_SIZE 0x8214
#define GL_FRAMEBUFFER_ATTACHMENT_ALPHA_SIZE 0x8215
#define GL_FRAMEBUFFER_ATTACHMENT_DEPTH_SIZE 0x8216
#define GL_FRAMEBUFFER_ATTACHMENT_STENCIL_SIZE 0x8217
#define GL_FRAMEBUFFER_DEFAULT 0x8218
#define GL_FRAMEBUFFER_UNDEFINED 0x8219
#define GL_DEPTH_STENCIL_ATTACHMENT 0x821A
#define GL_INDEX 0x8222
#define GL_MAX_RENDERBUFFER_SIZE 0x84E8
#define GL_DEPTH_STENCIL 0x84F9
#define GL_UNSIGNED_INT_24_8 0x84FA
#define GL_DEPTH24_STENCIL8 0x88F0
#define GL_TEXTURE_STENCIL_SIZE 0x88F1
#define GL_UNSIGNED_NORMALIZED 0x8C17
#define GL_SRGB 0x8C40
#define GL_DRAW_FRAMEBUFFER_BINDING 0x8CA6
#define GL_FRAMEBUFFER_BINDING 0x8CA6
#define GL_RENDERBUFFER_BINDING 0x8CA7
#define GL_READ_FRAMEBUFFER 0x8CA8
#define GL_DRAW_FRAMEBUFFER 0x8CA9
#define GL_READ_FRAMEBUFFER_BINDING 0x8CAA
#define GL_RENDERBUFFER_SAMPLES 0x8CAB
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_TYPE 0x8CD0
#define GL_FRAMEBUFFER_ATTACHMENT_OBJECT_NAME 0x8CD1
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LEVEL 0x8CD2
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_CUBE_MAP_FACE 0x8CD3
#define GL_FRAMEBUFFER_ATTACHMENT_TEXTURE_LAYER 0x8CD4
#define GL_FRAMEBUFFER_COMPLETE 0x8CD5
#define GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT 0x8CD6
#define GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT 0x8CD7
#define GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER 0x8CDB
#define GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER 0x8CDC
#define GL_FRAMEBUFFER_UNSUPPORTED 0x8CDD
#define GL_MAX_COLOR_ATTACHMENTS 0x8CDF
#define GL_COLOR_ATTACHMENT0 0x8CE0
#define GL_COLOR_ATTACHMENT1 0x8CE1
#define GL_COLOR_ATTACHMENT2 0x8CE2
#define GL_COLOR_ATTACHMENT3 0x8CE3
#define GL_COLOR_ATTACHMENT4 0x8CE4
#define GL_COLOR_ATTACHMENT5 0x8CE5
#define GL_COLOR_ATTACHMENT6 0x8CE6
#define GL_COLOR_ATTACHMENT7 0x8CE7
#define GL_COLOR_ATTACHMENT8 0x8CE8
#define GL_COLOR_ATTACHMENT9 0x8CE9
#define GL_COLOR_ATTACHMENT10 0x8CEA
#define GL_COLOR_ATTACHMENT11 0x8CEB
#define GL_COLOR_ATTACHMENT12 0x8CEC
#define GL_COLOR_ATTACHMENT13 0x8CED
#define GL_COLOR_ATTACHMENT14 0x8CEE
#define GL_COLOR_ATTACHMENT15 0x8CEF
#define GL_DEPTH_ATTACHMENT 0x8D00
#define GL_STENCIL_ATTACHMENT 0x8D20
#define GL_FRAMEBUFFER 0x8D40
#define GL_RENDERBUFFER 0x8D41
#define GL_RENDERBUFFER_WIDTH 0x8D42
#define GL_RENDERBUFFER_HEIGHT 0x8D43
#define GL_RENDERBUFFER_INTERNAL_FORMAT 0x8D44
#define GL_STENCIL_INDEX1 0x8D46
#define GL_STENCIL_INDEX4 0x8D47
#define GL_STENCIL_INDEX8 0x8D48
#define GL_STENCIL_INDEX16 0x8D49
#define GL_RENDERBUFFER_RED_SIZE 0x8D50
#define GL_RENDERBUFFER_GREEN_SIZE 0x8D51
#define GL_RENDERBUFFER_BLUE_SIZE 0x8D52
#define GL_RENDERBUFFER_ALPHA_SIZE 0x8D53
#define GL_RENDERBUFFER_DEPTH_SIZE 0x8D54
#define GL_RENDERBUFFER_STENCIL_SIZE 0x8D55
#define GL_FRAMEBUFFER_INCOMPLETE_MULTISAMPLE 0x8D56
#define GL_MAX_SAMPLES 0x8D57
//-------------------


//---------- Version 3.0

#define GL_CLIP_DISTANCE0 GL_CLIP_PLANE0
#define GL_CLIP_DISTANCE1 GL_CLIP_PLANE1
#define GL_CLIP_DISTANCE2 GL_CLIP_PLANE2
#define GL_CLIP_DISTANCE3 GL_CLIP_PLANE3
#define GL_CLIP_DISTANCE4 GL_CLIP_PLANE4
#define GL_CLIP_DISTANCE5 GL_CLIP_PLANE5
#define GL_COMPARE_REF_TO_TEXTURE GL_COMPARE_R_TO_TEXTURE_ARB
#define GL_MAX_CLIP_DISTANCES GL_MAX_CLIP_PLANES
#define GL_MAX_VARYING_COMPONENTS GL_MAX_VARYING_FLOATS
#define GL_CONTEXT_FLAG_FORWARD_COMPATIBLE_BIT 0x0001
#define GL_MAJOR_VERSION 0x821B
#define GL_MINOR_VERSION 0x821C
#define GL_NUM_EXTENSIONS 0x821D
#define GL_CONTEXT_FLAGS 0x821E
#define GL_DEPTH_BUFFER 0x8223
#define GL_STENCIL_BUFFER 0x8224
#define GL_RGBA32F 0x8814
#define GL_RGB32F 0x8815
#define GL_RGBA16F 0x881A
#define GL_RGB16F 0x881B
#define GL_VERTEX_ATTRIB_ARRAY_INTEGER 0x88FD
#define GL_MAX_ARRAY_TEXTURE_LAYERS 0x88FF
#define GL_MIN_PROGRAM_TEXEL_OFFSET 0x8904
#define GL_MAX_PROGRAM_TEXEL_OFFSET 0x8905
#define GL_CLAMP_VERTEX_COLOR 0x891A
#define GL_CLAMP_FRAGMENT_COLOR 0x891B
#define GL_CLAMP_READ_COLOR 0x891C
#define GL_FIXED_ONLY 0x891D
#define GL_TEXTURE_RED_TYPE 0x8C10
#define GL_TEXTURE_GREEN_TYPE 0x8C11
#define GL_TEXTURE_BLUE_TYPE 0x8C12
#define GL_TEXTURE_ALPHA_TYPE 0x8C13
#define GL_TEXTURE_LUMINANCE_TYPE 0x8C14
#define GL_TEXTURE_INTENSITY_TYPE 0x8C15
#define GL_TEXTURE_DEPTH_TYPE 0x8C16
#define GL_TEXTURE_1D_ARRAY 0x8C18
#define GL_PROXY_TEXTURE_1D_ARRAY 0x8C19
#define GL_TEXTURE_2D_ARRAY 0x8C1A
#define GL_PROXY_TEXTURE_2D_ARRAY 0x8C1B
#define GL_TEXTURE_BINDING_1D_ARRAY 0x8C1C
#define GL_TEXTURE_BINDING_2D_ARRAY 0x8C1D
#define GL_R11F_G11F_B10F 0x8C3A
#define GL_UNSIGNED_INT_10F_11F_11F_REV 0x8C3B
#define GL_RGB9_E5 0x8C3D
#define GL_UNSIGNED_INT_5_9_9_9_REV 0x8C3E
#define GL_TEXTURE_SHARED_SIZE 0x8C3F
#define GL_TRANSFORM_FEEDBACK_VARYING_MAX_LENGTH 0x8C76
#define GL_TRANSFORM_FEEDBACK_BUFFER_MODE 0x8C7F
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_COMPONENTS 0x8C80
#define GL_TRANSFORM_FEEDBACK_VARYINGS 0x8C83
#define GL_TRANSFORM_FEEDBACK_BUFFER_START 0x8C84
#define GL_TRANSFORM_FEEDBACK_BUFFER_SIZE 0x8C85
#define GL_PRIMITIVES_GENERATED 0x8C87
#define GL_TRANSFORM_FEEDBACK_PRIMITIVES_WRITTEN 0x8C88
#define GL_RASTERIZER_DISCARD 0x8C89
#define GL_MAX_TRANSFORM_FEEDBACK_INTERLEAVED_COMPONENTS 0x8C8A
#define GL_MAX_TRANSFORM_FEEDBACK_SEPARATE_ATTRIBS 0x8C8B
#define GL_INTERLEAVED_ATTRIBS 0x8C8C
#define GL_SEPARATE_ATTRIBS 0x8C8D
#define GL_TRANSFORM_FEEDBACK_BUFFER 0x8C8E
#define GL_TRANSFORM_FEEDBACK_BUFFER_BINDING 0x8C8F
#define GL_RGBA32UI 0x8D70
#define GL_RGB32UI 0x8D71
#define GL_RGBA16UI 0x8D76
#define GL_RGB16UI 0x8D77
#define GL_RGBA8UI 0x8D7C
#define GL_RGB8UI 0x8D7D
#define GL_RGBA32I 0x8D82
#define GL_RGB32I 0x8D83
#define GL_RGBA16I 0x8D88
#define GL_RGB16I 0x8D89
#define GL_RGBA8I 0x8D8E
#define GL_RGB8I 0x8D8F
#define GL_RED_INTEGER 0x8D94
#define GL_GREEN_INTEGER 0x8D95
#define GL_BLUE_INTEGER 0x8D96
#define GL_ALPHA_INTEGER 0x8D97
#define GL_RGB_INTEGER 0x8D98
#define GL_RGBA_INTEGER 0x8D99
#define GL_BGR_INTEGER 0x8D9A
#define GL_BGRA_INTEGER 0x8D9B
#define GL_SAMPLER_1D_ARRAY 0x8DC0
#define GL_SAMPLER_2D_ARRAY 0x8DC1
#define GL_SAMPLER_1D_ARRAY_SHADOW 0x8DC3
#define GL_SAMPLER_2D_ARRAY_SHADOW 0x8DC4
#define GL_SAMPLER_CUBE_SHADOW 0x8DC5
#define GL_UNSIGNED_INT_VEC2 0x8DC6
#define GL_UNSIGNED_INT_VEC3 0x8DC7
#define GL_UNSIGNED_INT_VEC4 0x8DC8
#define GL_INT_SAMPLER_1D 0x8DC9
#define GL_INT_SAMPLER_2D 0x8DCA
#define GL_INT_SAMPLER_3D 0x8DCB
#define GL_INT_SAMPLER_CUBE 0x8DCC
#define GL_INT_SAMPLER_1D_ARRAY 0x8DCE
#define GL_INT_SAMPLER_2D_ARRAY 0x8DCF
#define GL_UNSIGNED_INT_SAMPLER_1D 0x8DD1
#define GL_UNSIGNED_INT_SAMPLER_2D 0x8DD2
#define GL_UNSIGNED_INT_SAMPLER_3D 0x8DD3
#define GL_UNSIGNED_INT_SAMPLER_CUBE 0x8DD4
#define GL_UNSIGNED_INT_SAMPLER_1D_ARRAY 0x8DD6
#define GL_UNSIGNED_INT_SAMPLER_2D_ARRAY 0x8DD7
#define GL_QUERY_WAIT 0x8E13
#define GL_QUERY_NO_WAIT 0x8E14
#define GL_QUERY_BY_REGION_WAIT 0x8E15
#define GL_QUERY_BY_REGION_NO_WAIT 0x8E16


//---------------------3.2
#define GL_CONTEXT_CORE_PROFILE_BIT 0x00000001
#define GL_CONTEXT_COMPATIBILITY_PROFILE_BIT 0x00000002
#define GL_LINES_ADJACENCY 0x000A
#define GL_LINE_STRIP_ADJACENCY 0x000B
#define GL_TRIANGLES_ADJACENCY 0x000C
#define GL_TRIANGLE_STRIP_ADJACENCY 0x000D
#define GL_PROGRAM_POINT_SIZE 0x8642
#define GL_GEOMETRY_VERTICES_OUT 0x8916
#define GL_GEOMETRY_INPUT_TYPE 0x8917
#define GL_GEOMETRY_OUTPUT_TYPE 0x8918
#define GL_MAX_GEOMETRY_TEXTURE_IMAGE_UNITS 0x8C29
#define GL_FRAMEBUFFER_ATTACHMENT_LAYERED 0x8DA7
#define GL_FRAMEBUFFER_INCOMPLETE_LAYER_TARGETS 0x8DA8
#define GL_GEOMETRY_SHADER 0x8DD9
#define GL_MAX_GEOMETRY_UNIFORM_COMPONENTS 0x8DDF
#define GL_MAX_GEOMETRY_OUTPUT_VERTICES 0x8DE0
#define GL_MAX_GEOMETRY_TOTAL_OUTPUT_COMPONENTS 0x8DE1
#define GL_MAX_VERTEX_OUTPUT_COMPONENTS 0x9122
#define GL_MAX_GEOMETRY_INPUT_COMPONENTS 0x9123
#define GL_MAX_GEOMETRY_OUTPUT_COMPONENTS 0x9124
#define GL_MAX_FRAGMENT_INPUT_COMPONENTS 0x9125
#define GL_CONTEXT_PROFILE_MASK 0x9126
//----------------------------


// 4.0
#define GL_SAMPLE_SHADING 0x8C36
#define GL_MIN_SAMPLE_SHADING_VALUE 0x8C37
#define GL_MIN_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5E
#define GL_MAX_PROGRAM_TEXTURE_GATHER_OFFSET 0x8E5F
#define GL_MAX_PROGRAM_TEXTURE_GATHER_COMPONENTS 0x8F9F
#define GL_TEXTURE_CUBE_MAP_ARRAY 0x9009
#define GL_TEXTURE_BINDING_CUBE_MAP_ARRAY 0x900A
#define GL_PROXY_TEXTURE_CUBE_MAP_ARRAY 0x900B
#define GL_SAMPLER_CUBE_MAP_ARRAY 0x900C
#define GL_SAMPLER_CUBE_MAP_ARRAY_SHADOW 0x900D
#define GL_INT_SAMPLER_CUBE_MAP_ARRAY 0x900E
#define GL_UNSIGNED_INT_SAMPLER_CUBE_MAP_ARRAY 0x900F
//-------------------------------------------------------------------------


//------------------------------------------------------------------------- 4.3
#define GL_CONTEXT_FLAG_DEBUG_BIT 0x00000002
#define GL_STACK_OVERFLOW 0x0503
#define GL_STACK_UNDERFLOW 0x0504
#define GL_DEBUG_OUTPUT_SYNCHRONOUS 0x8242
#define GL_DEBUG_NEXT_LOGGED_MESSAGE_LENGTH 0x8243
#define GL_DEBUG_CALLBACK_FUNCTION 0x8244
#define GL_DEBUG_CALLBACK_USER_PARAM 0x8245
#define GL_DEBUG_SOURCE_API 0x8246
#define GL_DEBUG_SOURCE_WINDOW_SYSTEM 0x8247
#define GL_DEBUG_SOURCE_SHADER_COMPILER 0x8248
#define GL_DEBUG_SOURCE_THIRD_PARTY 0x8249
#define GL_DEBUG_SOURCE_APPLICATION 0x824A
#define GL_DEBUG_SOURCE_OTHER 0x824B
#define GL_DEBUG_TYPE_ERROR 0x824C
#define GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR 0x824D
#define GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR 0x824E
#define GL_DEBUG_TYPE_PORTABILITY 0x824F
#define GL_DEBUG_TYPE_PERFORMANCE 0x8250
#define GL_DEBUG_TYPE_OTHER 0x8251
#define GL_DEBUG_TYPE_MARKER 0x8268
#define GL_DEBUG_TYPE_PUSH_GROUP 0x8269
#define GL_DEBUG_TYPE_POP_GROUP 0x826A
#define GL_DEBUG_SEVERITY_NOTIFICATION 0x826B
#define GL_MAX_DEBUG_GROUP_STACK_DEPTH 0x826C
#define GL_DEBUG_GROUP_STACK_DEPTH 0x826D
#define GL_BUFFER 0x82E0
#define GL_SHADER 0x82E1
#define GL_PROGRAM 0x82E2
#define GL_QUERY 0x82E3
#define GL_PROGRAM_PIPELINE 0x82E4
#define GL_SAMPLER 0x82E6
#define GL_DISPLAY_LIST 0x82E7
#define GL_MAX_LABEL_LENGTH 0x82E8
#define GL_MAX_DEBUG_MESSAGE_LENGTH 0x9143
#define GL_MAX_DEBUG_LOGGED_MESSAGES 0x9144
#define GL_DEBUG_LOGGED_MESSAGES 0x9145
#define GL_DEBUG_SEVERITY_HIGH 0x9146
#define GL_DEBUG_SEVERITY_MEDIUM 0x9147
#define GL_DEBUG_SEVERITY_LOW 0x9148
#define GL_DEBUG_OUTPUT 0x92E0
//-------------------------------------------------------------------------

unsigned int OpenGLRenderBufferAttachmentPointToID(const OpenGLRenderBufferAttachmentPoint renderBufferAttachmentPoint)
{
    switch (renderBufferAttachmentPoint)
    {
    case OpenGLRenderBufferAttachmentPointColor: return GL_COLOR_ATTACHMENT0;
    case OpenGLRenderBufferAttachmentPointDepth: return GL_DEPTH_ATTACHMENT;
    case OpenGLRenderBufferAttachmentPointStencil: return GL_STENCIL_ATTACHMENT;

    case OpenGLRenderBufferAttachmentPointInvalid:
    default:
        return -1;
    }
}

int OpenGLImageFormatToID(const OpenGLImageFormat imageFormat)
{
    switch (imageFormat)
    {
    case OpenGLImageFormatColorIndex: return GL_COLOR_INDEX;
    case OpenGLImageFormatStencilIndex: return GL_STENCIL_INDEX;
    case OpenGLImageFormatDepthComponent: return GL_DEPTH_COMPONENT;
    case OpenGLImageFormatRed: return GL_RED;
    case OpenGLImageFormatGreen: return GL_GREEN;
    case OpenGLImageFormatBlue: return GL_BLUE;
    case OpenGLImageFormatAlpha: return GL_ALPHA;
    case OpenGLImageFormatRGB: return GL_RGB;
    case OpenGLImageFormatRGBA: return GL_RGBA;
    //case OpenGLImageFormatBGR: return GL_BGR;
    //case OpenGLImageFormatBGRA: return GL_BGRA;
    case OpenGLImageFormatLuminance: return GL_LUMINANCE;
    case OpenGLImageFormatLuminanceAlpha: return GL_LUMINANCE_ALPHA;
    default:
        return -1;
    }
}

int OpenGLDataTypeToID(const OpenGLDataType dataType)
{
    switch (dataType)
    {
    case OpenGLTypeByteSigned:
        return GL_BYTE;

    case OpenGLTypeByteUnsigned:
        return GL_UNSIGNED_BYTE;

    case OpenGLTypeShortSigned:
        return GL_SHORT;

    case OpenGLTypeShortUnsigned:
        return GL_UNSIGNED_SHORT;

    case OpenGLTypeIntegerSigned:
        return GL_INT;

    case OpenGLTypeIntegerUnsigned:
        return GL_UNSIGNED_INT;

    case OpenGLTypeFloat:
        return GL_FLOAT;

    case OpenGLTypeDouble:
        return GL_DOUBLE;

    default:
        return -1;
    }
}

CPrivate int OpenGLRenderBufferFormatToID(const OpenGLRenderBufferFormat dataType)
{
    switch (dataType)
    {
        case OpenGLRenderBufferFormatDepth24Stencil8: return GL_DEPTH24_STENCIL8;
        case OpenGLRenderBufferFormatInvalid:
        default:
            return -1;
    }
}

int OpenGLRenderModeToID(const OpenGLRenderMode openGLRenderMode)
{
    switch (openGLRenderMode)
    {
        case OpenGLRenderPoints: return GL_POINTS;
        case OpenGLRenderLines: return GL_LINES;
        case OpenGLRenderLineLoop: return GL_LINE_LOOP;
        case OpenGLRenderLineStrip: return GL_LINE_STRIP;
        case OpenGLRenderTriangles: return GL_TRIANGLES;
        case OpenGLRenderTriangleStrip: return GL_TRIANGLE_STRIP;
        case OpenGLRenderTriangleFan: return GL_TRIANGLE_FAN;
        case OpenGLRenderQuads: return GL_QUADS;
        case OpenGLRenderQuadStrip: return GL_QUAD_STRIP;
        case OpenGLRenderPolygon: return GL_POLYGON;

        default:
            return -1;
    }
}

unsigned int OpenGLTextureTypeToID(const OpenGLTextureType openGLTextureType)
{
    switch (openGLTextureType)
    {
    case OpenGLTextureType1D: return  GL_TEXTURE_1D;
    case OpenGLTextureType2D:return  GL_TEXTURE_2D;
    case OpenGLTextureType3D:return   GL_TEXTURE_3D;
    case OpenGLTextureType1DArray:return   GL_TEXTURE_1D_ARRAY;
    case OpenGLTextureType2DArray:return   GL_TEXTURE_2D_ARRAY;
    //case OpenGLTextureTypeRectangle:return   GL_TEXTURE_RECTANGLE;
    case OpenGLTextureTypeCubeMap:return  GL_TEXTURE_CUBE_MAP;
    case OpenGLTextureTypeCubleMapArray:return   GL_TEXTURE_CUBE_MAP_ARRAY;
   // case OpenGLTextureTypeBuffer:return   GL_TEXTURE_BUFFER;
   // case OpenGLTextureType2DMultiSample:return   GL_TEXTURE_2D_MULTISAMPLE;
   // case OpenGLTextureType2DMultiSampleArray:return   GL_TEXTURE_2D_MULTISAMPLE_ARRAY;
    case OpenGLTextureTypeInvalid:
    default:
        return -1;
    }
}

CPrivate OpenGLVersion OpenGLVersionParse(const unsigned int versionID)
{
    switch (versionID)
    {
    case MakeInt(0, 1, 0, 0): return OpenGLVersion1x0x0;
    case MakeInt(0, 1, 1, 0): return OpenGLVersion1x1x0;
    case MakeInt(0, 1, 2, 0): return OpenGLVersion1x2x0;
    case MakeInt(0, 1, 2, 1): return OpenGLVersion1x2x1;
    case MakeInt(0, 1, 3, 0): return OpenGLVersion1x3x0;
    case MakeInt(0, 1, 4, 0): return OpenGLVersion1x4x0;
    case MakeInt(0, 1, 5, 0): return OpenGLVersion1x5x0;
    case MakeInt(0, 2, 0, 0): return OpenGLVersion2x0x0;
    case MakeInt(0, 2, 1, 0): return OpenGLVersion2x1x0;
    case MakeInt(0, 3, 0, 0): return OpenGLVersion3x0x0;
    case MakeInt(0, 3, 1, 0): return OpenGLVersion3x1x0;
    case MakeInt(0, 3, 2, 0): return OpenGLVersion3x2x0;
    case MakeInt(0, 3, 3, 0): return OpenGLVersion3x3x0;
    case MakeInt(0, 4, 0, 0): return OpenGLVersion4x0x0;
    case MakeInt(0, 4, 1, 0): return OpenGLVersion4x1x0;
    case MakeInt(0, 4, 2, 0): return OpenGLVersion4x2x0;
    case MakeInt(0, 4, 3, 0): return OpenGLVersion4x3x0;
    case MakeInt(0, 4, 4, 0): return OpenGLVersion4x4x0;
    case MakeInt(0, 4, 5, 0): return OpenGLVersion4x5x0;
    case MakeInt(0, 4, 6, 0): return OpenGLVersion4x6x0;
    default: return  OpenGLVersionInvalid;
    }
}

void OpenGLCacheFunction(void** loadList, size_t* currentSize, char* name, void* functionADress)
{
    size_t index = *currentSize;

    loadList[index] = functionADress;
    loadList[index + 1] = name;

    *currentSize += 2u;
}

const void* const OpenGLFunctionAdressFetch(const char* const functionName)
{
    const void* const functionAdress =
#if OSUnix
    (const void* const)glXGetProcAddress(functionName);
#elif OSWindows
    (const void* const)wglGetProcAddress(functionName);

    switch((size_t)functionAdress)
    {
        case -1: // fall though
        case 0x0: // fall though
        case 0x1: // fall though
        case 0x2: // fall though
        case 0x3:
            return 0x0;
        // default: do nothing
    }
#endif

    return functionAdress;
}

void OpenGLContextConstruct(OpenGLContext* const openGLContext)
{
    MemorySet(openGLContext, sizeof(OpenGLContext), 0);
}

void OpenGLContextDestruct(OpenGLContext* const openGLContext)
{

}

void OpenGLContextCreate(OpenGLContext* const openGLContext)
{
    PXWindow* const window = (PXWindow* const)openGLContext->AttachedWindow; // can be null, if no windows is supposed to be used

#if OSUnix
    //glXCreateContext(window->DisplayCurren, ) // TODO:::

    glXMakeCurrent(window->DisplayCurrent, window->ID, openGLContext->OpenGLConext);

#elif OSWindows
  
    const HGLRC handle = wglCreateContext(window->HandleDeviceContext);

    // Check if failed
    {
        const unsigned char successful = handle != 0;

        if (!successful)
        {
            const ActionResult actionResult = GetCurrentError();

            // return actionResult;
        }
    }

    openGLContext->OpenGLConext = handle;

#endif

    OpenGLContextSelect(openGLContext);


    const char* vendor = glGetString(GL_VENDOR); // Returns the company responsible for this GL implementation.This name does not change from release to release.

    TextCopyA(vendor, -1, openGLContext->Vendor, 64);

    const char* renderer = glGetString(GL_RENDERER); //   Returns the name of the renderer.This name is typically specific to a particular configuration of a hardware platform.It does not change from release to release.

    TextCopyA(renderer, -1, openGLContext->Renderer, 64);

    const char* version = glGetString(GL_VERSION); //    Returns a version or release number.

    TextCopyA(version, -1, openGLContext->VersionText, 64);
    // glGetString(GL_SHADING_LANGUAGE_VERSION); //   Returns a version or release number for the shading language.

// Parse version
    {
        int versionMajor = 0;
        int versionMinor = 0;
        int versionPatch = 0;
        size_t offset = 0;

        offset += TextToIntA(version + offset, 64, &versionMajor);
        offset += 1u; // dot
        offset += TextToIntA(version + offset, 64, &versionMinor);
        offset += 1u; // dot
        offset += TextToIntA(version + offset, 64, &versionPatch);

        const unsigned int id = MakeInt(0, versionMajor, versionMinor, versionPatch);

        openGLContext->Version = OpenGLVersionParse(id);
    }

    // Fetch functions

    size_t length = 0;
    void* functionNameList[128];

    switch (openGLContext->Version)
    {
    default: return;

    case OpenGLVersion4x6x0:
    {
        // Fall though1
    }
    case OpenGLVersion4x5x0:
    {
        // Fall though1
    }
    case OpenGLVersion4x4x0:
    {
        // Fall though1
    }
    case OpenGLVersion4x3x0:
    {
        OpenGLCacheFunction(functionNameList, &length, "glDebugMessageCallback", &openGLContext->OpenGLDebugMessageCallback);

        // Fall though1
    }
    case OpenGLVersion4x2x0:
    {
        // Fall though1
    }
    case OpenGLVersion4x1x0:
    {
        OpenGLCacheFunction(functionNameList, &length, "glVertexAttribLPointer", &openGLContext->OpenGLVertexAttribLPointerCallBack);

        // Fall though1
    }
    case OpenGLVersion4x0x0:
    {
        // Fall though1
    }
    case OpenGLVersion3x3x0:
    {
        // Fall though1
    }
    case OpenGLVersion3x2x0:
    {
        // Fall though1
    }
    case OpenGLVersion3x1x0:
    {
        // Fall though1
    }
    case OpenGLVersion3x0x0:
    {
        OpenGLCacheFunction(functionNameList, &length, "glGenFramebuffers", &openGLContext->OpenGLFrameBufferCreateCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDeleteFramebuffers", &openGLContext->OpenGLFrameBufferDeleteCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBindFramebuffer", &openGLContext->OpenGLFrameBufferBindCallBack);

        OpenGLCacheFunction(functionNameList, &length, "glGenRenderbuffers", &openGLContext->OpenGLRenderBufferCreateCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBindRenderbuffer", &openGLContext->OpenGLRenderBufferBindCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDeleteRenderbuffers", &openGLContext->OpenGLRenderBufferDeleteCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glRenderbufferStorage", &openGLContext->OpenGLRenderBufferStorageCallBack);

        OpenGLCacheFunction(functionNameList, &length, "glFramebufferTexture2D", &openGLContext->OpenGLFrameBufferLinkTexture2DCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glFramebufferRenderbuffer", &openGLContext->OpenGLFrameBufferLinkRenderBufferCallBack);

        OpenGLCacheFunction(functionNameList, &length, "glGenVertexArrays", &openGLContext->OpenGLGenVertexArraysCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBindVertexArray", &openGLContext->OpenGLBindVertexArrayCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glVertexAttribIPointer", &openGLContext->OpenGLVertexAttribIPointerCallBack);

        // Fall though1
    }
    case OpenGLVersion2x1x0:
    {
        // Fall though1
    }
    case OpenGLVersion2x0x0:
    {
        OpenGLCacheFunction(functionNameList, &length, "glGenTextures", &openGLContext->OpenGLTextureCreateCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBindTexture", &openGLContext->OpenGLTextureBindCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDeleteTextures", &openGLContext->OpenGLTextureDeleteCallBack);

        OpenGLCacheFunction(functionNameList, &length, "glCreateProgram", &openGLContext->OpenGLShaderProgramCreateCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUseProgram", &openGLContext->OpenGLShaderProgramUseCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDeleteProgram", &openGLContext->OpenGLShaderProgramDeleteCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glShaderSource", &openGLContext->OpenGLShaderSourceCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glCreateShader", &openGLContext->OpenGLShaderCreateCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glCompileShader", &openGLContext->OpenGLShaderCompileCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glGetShaderiv", &openGLContext->OpenGLShaderGetivCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glGetShaderInfoLog", &openGLContext->OpenGLShaderLogInfoGetCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDeleteShader", &openGLContext->OpenGLShaderDeleteCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glAttachShader", &openGLContext->OpenGLAttachShaderCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glLinkProgram", &openGLContext->OpenGLLinkProgramCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glValidateProgram", &openGLContext->OpenGLValidateProgramCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glActiveTexture", &openGLContext->OpenGLActiveTextureCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glGenBuffers", &openGLContext->OpenGLGenBuffersCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBindBuffer", &openGLContext->OpenGLBindBufferCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glBufferData", &openGLContext->OpenGLBufferDataCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glVertexAttribPointer", &openGLContext->OpenGLVertexAttribPointerCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDisableVertexAttribArray", &openGLContext->OpenGLDisableVertexAttribArrayCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glDisableVertexArrayAttrib", &openGLContext->OpenGLDisableVertexArrayAttribCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glGetUniformLocation", &openGLContext->OpenGLGetUniformLocation);
        OpenGLCacheFunction(functionNameList, &length, "glUniform1f", &openGLContext->OpenGLUniform1fCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform1fv", &openGLContext->OpenGLUniform1fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform1i", &openGLContext->OpenGLUniform1iCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform1iv", &openGLContext->OpenGLUniform1ivCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform2f", &openGLContext->OpenGLUniform2fCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform2fv", &openGLContext->OpenGLUniform2fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform2i", &openGLContext->OpenGLUniform2iCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform2iv", &openGLContext->OpenGLUniform2ivCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform3f", &openGLContext->OpenGLUniform3fCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform3fv", &openGLContext->OpenGLUniform3fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform3i", &openGLContext->OpenGLUniform3iCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform3iv", &openGLContext->OpenGLUniform3ivCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform4f", &openGLContext->OpenGLUniform4fCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform4fv", &openGLContext->OpenGLUniform4fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform4i", &openGLContext->OpenGLUniform4iCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniform4iv", &openGLContext->OpenGLUniform4ivCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniformMatrix2fv", &openGLContext->OpenGLUniformMatrix2fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniformMatrix3fv", &openGLContext->OpenGLUniformMatrix3fvCallBack);
        OpenGLCacheFunction(functionNameList, &length, "glUniformMatrix4fv", &openGLContext->OpenGLUniformMatrix4fvCallBack);

        // Fall though1
    }
    case OpenGLVersion1x5x0:
    {
        // Fall though1
    }
    case OpenGLVersion1x4x0:
    {
        // Fall though1
    }
    case OpenGLVersion1x3x0:
    {
        // Fall though1
    }
    case OpenGLVersion1x2x1:
    {
        // Fall though1
    }
    case OpenGLVersion1x2x0:
    {
        // Fall though1
    }
    case OpenGLVersion1x1x0:
    {
        /*
        const char* functionNameList[50];

        functionNameList[0] = "glActiveTexture";
        functionNameList[0] = "glAlphaFunc";
        functionNameList[0] = "glBindBuffer";
        functionNameList[0] = "glBindTexture";
        functionNameList[0] = "glBlendFunc";
        functionNameList[0] = "glBufferData";
        functionNameList[0] = "glBufferSubData";
        functionNameList[0] = "glClear";
        functionNameList[0] = "glClearColor";
        functionNameList[0] = "glClearDepth";
        functionNameList[0] = "glClearStencil";
        functionNameList[0] = "glClientActiveTexture";
        functionNameList[0] = "glClipPlane";
        functionNameList[0] = "glColor";
        functionNameList[0] = "glColorMask";
        functionNameList[0] = "glColorPointer";
        functionNameList[0] = "glCompressedTexImage2D";
        functionNameList[0] = "glCompressedTexSubImage2D";
        functionNameList[0] = "glCopyTexImage2D";
        functionNameList[0] = "glCopyTexSubImage2D";
        functionNameList[0] = "glCullFace";
        functionNameList[0] = "glCurrentPaletteMatrix";
        functionNameList[0] = "glDeleteBuffers";
        functionNameList[0] = "glDeleteTextures";
        functionNameList[0] = "glDepthFunc";
        functionNameList[0] = "glDepthMask";
        functionNameList[0] = "glDepthRange";
        functionNameList[0] = "glDrawArrays";
        functionNameList[0] = "glDrawElements";
        functionNameList[0] = "glDrawTex";
        functionNameList[0] = "glEnable";
        functionNameList[0] = "glEnableClientState";
        functionNameList[0] = "glFinish";
        functionNameList[0] = "glFlush";
        functionNameList[0] = "glFog";
        functionNameList[0] = "glFrontFace";
        functionNameList[0] = "glFrustum";
        functionNameList[0] = "glGenBuffers";
        functionNameList[0] = "glGenTextures";
        functionNameList[0] = "glGet";
        functionNameList[0] = "glGetBufferParameteriv";
        functionNameList[0] = "glGetClipPlane";
        functionNameList[0] = "glGetError";
        functionNameList[0] = "glGetLight";
        functionNameList[0] = "glGetMaterial";
        functionNameList[0] = "glGetPointerv";
        functionNameList[0] = "glGetString";
        functionNameList[0] = "glGetTexEnv";
        functionNameList[0] = "glGetTexParameter";
        functionNameList[0] = "glHint";
        functionNameList[0] = "glIntro";
        functionNameList[0] = "glIsBuffer";
        functionNameList[0] = "glIsEnabled";
        functionNameList[0] = "glIsTexture";
        functionNameList[0] = "glLight";
        functionNameList[0] = "glLightModel";
        functionNameList[0] = "glLineWidth";
        functionNameList[0] = "glLoadIdentity";
        functionNameList[0] = "glLoadMatrix";
        functionNameList[0] = "glLoadPaletteFromModelViewMatrix";
        functionNameList[0] = "glLogicOp";
        functionNameList[0] = "glMaterial";
        functionNameList[0] = "glMatrixIndexPointer";
        functionNameList[0] = "glMatrixMode";
        functionNameList[0] = "glMultMatrix";
        functionNameList[0] = "glMultiTexCoord";
        functionNameList[0] = "glNormal";
        functionNameList[0] = "glNormalPointer";
        functionNameList[0] = "glOrtho";
        functionNameList[0] = "glPixelStorei";
        functionNameList[0] = "glPointParameter";
        functionNameList[0] = "glPointSize";
        functionNameList[0] = "glPointSizePointerOES";
        functionNameList[0] = "glPolygonOffset";
        functionNameList[0] = "glPushMatrix";
        functionNameList[0] = "glQueryMatrix";
        functionNameList[0] = "glReadPixels";
        functionNameList[0] = "glRotate";
        functionNameList[0] = "glSampleCoverage";
        functionNameList[0] = "glScale";
        functionNameList[0] = "glScissor";
        functionNameList[0] = "glShadeModel";
        functionNameList[0] = "glStencilFunc";
        functionNameList[0] = "glStencilMask";
        functionNameList[0] = "glStencilOp";
        functionNameList[0] = "glTexCoordPointer";
        functionNameList[0] = "glTexEnv";
        functionNameList[0] = "glTexImage2D";
        functionNameList[0] = "glTexParameter";
        functionNameList[0] = "glTexSubImage2D";
        functionNameList[0] = "glTranslate";
        functionNameList[0] = "glVertexPointer";
        functionNameList[0] = "glViewport";
        functionNameList[0] = "glWeightPointer";

        for (size_t i = 0; i < length; ++i)
        {
            const char* const functioName = functionNameList[i];

            OpenGLFunctionFetch();
        }
        */

        // Fall though1
    }
    case OpenGLVersion1x0x0:
    {
        // Is connected staticly, no fetching needed.
    }
    }

    for (size_t i = 0; i < length; i += 2)
    {
        void** functionAdress = functionNameList[i];
        const char* functionName = functionNameList[i + 1];

        *functionAdress = OpenGLFunctionAdressFetch(functionName);
    }

    if (openGLContext->OpenGLDebugMessageCallback)
    {
        (openGLContext->OpenGLDebugMessageCallback)(OpenGLErrorMessageCallback, 0);
        glEnable(GL_DEBUG_OUTPUT);
    }

    OpenGLViewSize(openGLContext, 0, 0, window->Width, window->Height);
}

void OpenGLContextCreateWindowless(OpenGLContext* const openGLContext, const size_t width, const size_t height)
{
#if OSWindows

    if (!openGLContext->AttachedWindow) // if not set, we want a "hidden" window. Windows needs a window to make a OpenGL context.. for some reason.
    {
        PXWindow* const window = (PXWindow* const)MemoryAllocate(sizeof(PXWindow) * 1u);

        PXWindowConstruct(window);

        PXWindowCreateHidden(window, width, height, 1u); // This will call this function again. Recursive

        while (!window->IsRunning) // Wait
        {
            printf("");
        }

        openGLContext->AttachedWindow = window;

        MemoryCopy(&window->GraphicInstance.OpenGLInstance, sizeof(OpenGLContext), openGLContext, sizeof(OpenGLContext));

        return; // We should have all data here, stoping.
    }
#endif
}

void OpenGLContextSelect(OpenGLContext* const openGLContext)
{
    const PXWindow* const window = (const PXWindow* const)openGLContext->AttachedWindow;

#if OSUnix
    const int result = glXMakeCurrent(window->DisplayCurrent, window->ID, openGLContext->OpenGLConext);
#elif OSWindows
    const BOOL result = wglMakeCurrent(window->HandleDeviceContext, openGLContext->OpenGLConext);
#endif
}

unsigned char OpenGLContextDeselect(OpenGLContext* const openGLContext)
{
    const PXWindow* const window = (const PXWindow* const)openGLContext->AttachedWindow;

    const unsigned char successful =
#if OSUnix
        glXMakeCurrent(0, window->ID, openGLContext->OpenGLConext);
#elif OSWindows
        wglMakeCurrent(0, 0);
#endif

    return successful;
}

void OpenGLContextRelease(OpenGLContext* const openGLContext)
{
    const PXWindow* const window = (const PXWindow* const)openGLContext->AttachedWindow;

#if OSUnix
    const int result = glXMakeCurrent(window->DisplayCurrent,0, 0);

#elif OSWindows

#endif
}

void OpenGLRenderBufferSwap(OpenGLContext* const openGLContext)
{
    const PXWindow* const window = (const PXWindow* const)openGLContext->AttachedWindow;

#if OSUnix
    glXSwapBuffers(window->DisplayCurrent, window->ID);

#elif OSWindows
    BOOL successful = SwapBuffers(window->HandleDeviceContext);

    successful += 0;
#endif
}

void OpenGLFlush(OpenGLContext* const openGLContext)
{
    glFlush();
}

void OpenGLViewSize(OpenGLContext* const openGLContext, const size_t x, const size_t y, const size_t width, const size_t height)
{
    glViewport(x, y, width, height);
}

void OpenGLClearColor(OpenGLContext* const openGLContext, const float red, const float green, const float blue, const float alpha)
{
    glClearColor(red, green, blue, alpha);
}

void OpenGLClear(OpenGLContext* const openGLContext, const unsigned int clearID)
{
    glClear(clearID);
}

void OpenGLDrawScaleF(OpenGLContext* const openGLContext, const float x, const float y, const float z)
{
    glScaled(x, y, z);
}

void OpenGLDrawBegin(OpenGLContext* const openGLContext, const OpenGLRenderMode openGLRenderMode)
{
    const int openGLRenderModeID = OpenGLRenderModeToID(openGLRenderMode);

    glBegin(openGLRenderModeID);
}

void OpenGLDrawVertexXYZF(OpenGLContext* const openGLContext, const float x, const float y, const float z)
{
    glVertex3f(x, y, z);
}

void OpenGLDrawColorRGBF(OpenGLContext* const openGLContext, const float red, const float green, const float blue)
{
    glColor3f(red, green, blue);
}

void OpenGLDrawEnd(OpenGLContext* const openGLContext)
{
    glEnd();
}

void APIENTRY OpenGLErrorMessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const char* message, const void* userParam)
{
    unsigned char openGLspecific = type == GL_DEBUG_TYPE_ERROR;
    const char* sourceText = 0;
    const char* typeText = 0;
    const char* servertyText = 0;

    switch (source)
    {
    case GL_DEBUG_SOURCE_API:
        sourceText = "API";
        break;

    case GL_DEBUG_SOURCE_WINDOW_SYSTEM:
        sourceText = "Window";
        break;

    case GL_DEBUG_SOURCE_SHADER_COMPILER:
        sourceText = "Shader";
        break;

    case GL_DEBUG_SOURCE_THIRD_PARTY:
        sourceText = "3rd Party";
        break;

    case GL_DEBUG_SOURCE_APPLICATION:
        sourceText = "Application";
        break;

    case GL_DEBUG_SOURCE_OTHER:
        sourceText = "Other";
        break;

    default:
        break;
    }

    switch (type)
    {
    case GL_DEBUG_TYPE_ERROR:
        typeText = "Error";
        break;

    case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR:
        typeText = "DEPRECATED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
        typeText = "UNDEFINED_BEHAVIOR";
        break;

    case GL_DEBUG_TYPE_PORTABILITY:
        typeText = "PORTABILITY";
        break;

    case GL_DEBUG_TYPE_PERFORMANCE:
        typeText = "PERFORMANCE";
        break;

    case GL_DEBUG_TYPE_OTHER:
        typeText = "OTHER";
        break;

    case GL_DEBUG_TYPE_MARKER:
        typeText = "MARKER";
        break;

    case GL_DEBUG_TYPE_PUSH_GROUP:
        typeText = "PUSH_GROUP";
        break;

    case GL_DEBUG_TYPE_POP_GROUP:
        typeText = "POP_GROUP";
        break;

    default:
        break;
    }

    switch (severity)
    {
    case GL_DEBUG_SEVERITY_HIGH:
        servertyText = "High";
        break;

    case GL_DEBUG_SEVERITY_MEDIUM:
        servertyText = "Medium";
        break;

    case GL_DEBUG_SEVERITY_LOW:
        servertyText = "Low";
        break;

    case GL_DEBUG_SEVERITY_NOTIFICATION:
        servertyText = "Info";
        break;

    default:
        break;
    }

    fprintf
    (
        stderr,
        "[x][OpenGL][%s][%s][%s] %s\n",
        sourceText,
        typeText,
        servertyText,
        message
    );
}




/*

OpenGLID OpenGLToRenderMode(const GraphicRenderMode renderMode)
{
    switch (renderMode)
    {
    case GraphicRenderModePoint:
        return GL_POINTS;

    case GraphicRenderModeLine:
        return GL_LINES;

        // case GraphicRenderModeLineAdjacency:
          //   return GL_LINES_ADJACENCY;

       //  case GraphicRenderModeLineStripAdjacency:
        //     return GL_LINE_STRIP_ADJACENCY;

    case GraphicRenderModeLineLoop:
        return GL_LINE_LOOP;

    case GraphicRenderModeLineStrip:
        return GL_LINE_STRIP;

    case GraphicRenderModeTriangle:
        return GL_TRIANGLES;

        // case GraphicRenderModeTriangleAdjacency:
        //     return GL_TRIANGLES_ADJACENCY;

    case GraphicRenderModeTriangleFAN:
        return GL_TRIANGLE_FAN;

    case GraphicRenderModeTriangleStrip:
        return GL_TRIANGLE_STRIP;

        //   case GraphicRenderModeTriangleStripAdjacency:
          //     return GL_TRIANGLE_STRIP_ADJACENCY;

    case GraphicRenderModeSquare:
        return GL_QUADS;

        //  case GraphicRenderModePatches:
         //     return GL_PATCHES;

    default:
    case GraphicRenderModeInvalid:
        return -1;
    };
}

*/



































































/*



/*


GlmfBeginGlsBlock
GlmfCloseMetaFile
GlmfEndGlsBlock
GlmfEndPlayback
GlmfInitPlayback
GlmfPlayGlsRecord

wglChoosePixelFormat
wglCopyContext
wglCreateContext
wglCreateLayerContext
wglDeleteContext
wglDescribeLayerPlane
wglDescribePixelFormat
wglGetCurrentContext
wglGetCurrentDC
wglGetDefaultProcAddress
wglGetLayerPaletteEntries
wglGetPixelFormat
wglGetProcAddress
wglMakeCurrent
wglRealizeLayerPalette
wglSetLayerPaletteEntries
wglSetPixelFormat
wglShareLists
wglSwapBuffers
wglSwapLayerBuffers
wglSwapMultipleBuffers
wglUseFontBitmapsA
wglUseFontBitmapsW
wglUseFontOutlinesA
wglUseFontOutlinesW




// Opengl32.lib

    wglCopyContext
   -- wglCreateContext
    wglCreateLayerContext
   -- wglDeleteContext
    wglDescribeLayerPlane
    wglGetCurrentContext
    wglGetCurrentDC
    wglGetLayerPaletteEntries
    wglGetProcAddress
    wglMakeCurrent
    wglRealizeLayerPalette
    wglSetLayerPaletteEntries
    wglShareLists
    wglSwapLayerBuffers
    wglUseFontBitmaps
    wglUseFontOutlines


*/


/*
windows only


    ChoosePixelFormat
    DescribePixelFormat
    GetEnhMetaFilePixelFormat
    GetPixelFormat
    SetPixelFormat
    SwapBuffers



    GLYPHMETRICSFLOAT
    LAYERPLANEDESCRIPTOR
    PIXELFORMATDESCRIPTOR
    POINTFLOAT


* /

void OpenGLAddFunction(void** loadList, size_t* currentSize, char* name, void* functionADress)
{
    size_t index = *currentSize;

    loadList[index] = functionADress;
    loadList[index + 1] = name;

    *currentSize += 2u;
}
/*
OpenGLID OpenGLToShaderType(const ShaderType shaderType)
{
    switch (shaderType)
    {
    //case ShaderTypeVertex:
    //    return GL_VERTEX_SHADER;

    case   ShaderTypeTessellationControl:
        return -1; // ???

    case   ShaderTypeTessellationEvaluation:
        return -1; // ???

   // case   ShaderTypeGeometry:
  //      return GL_GEOMETRY_SHADER;

  //  case   ShaderTypeFragment:
  //      return GL_FRAGMENT_SHADER;

//    case  ShaderTypeCompute:
 //       return GL_COMPUTE_SHADER;

    case ShaderTypeUnkown:
    default:
        return -1;
    }
}

OpenGLID OpenGLToImageFormat(const ImageDataFormat imageFormat)
{
    switch (imageFormat)
    {
   // case ImageDataFormatBGR8:
   //     return GL_BGR;

  //  case ImageDataFormatBGRA8:
  //      return GL_BGRA;

    case ImageDataFormatRGB8:
        return GL_RGB;

    case ImageDataFormatRGBA8:
        return GL_RGBA;

    case ImageDataFormatAlphaMask:
    default:
        return -1;
    }
}

OpenGLID OpenGLToImageType(const GraphicImageType imageType)
{
    switch (imageType)
    {
    case GraphicImageTypeTexture2D:
        return GL_TEXTURE_2D;

    //case GraphicImageTypeTexture3D:
   //     return GL_TEXTURE_3D;

    case GraphicImageTypeTextureCubeContainer:
        return GL_TEXTURE_CUBE_MAP;

    case GraphicImageTypeTextureCubeRight:
        return GL_TEXTURE_CUBE_MAP_POSITIVE_X;

    case GraphicImageTypeTextureCubeLeft:
        return GL_TEXTURE_CUBE_MAP_NEGATIVE_X;

    case GraphicImageTypeTextureCubeTop:
        return GL_TEXTURE_CUBE_MAP_POSITIVE_Y;

    case GraphicImageTypeTextureCubeDown:
        return GL_TEXTURE_CUBE_MAP_NEGATIVE_Y;

    case GraphicImageTypeTextureCubeBack:
        return GL_TEXTURE_CUBE_MAP_POSITIVE_Z;

    case GraphicImageTypeTextureCubeFront:
        return GL_TEXTURE_CUBE_MAP_NEGATIVE_Z;

    default:
        return -1;
    }
}

OpenGLID OpenGLToImageWrap(const GraphicImageWrap imageWrap)
{
    switch (imageWrap)
    {
    case GraphicImageWrapNoModification:
        return GL_CLAMP_TO_BORDER;

   // case GraphicImageWrapStrechEdges:
    //    return GL_CLAMP_TO_EDGE;

   // case GraphicImageWrapStrechEdgesAndMirror:
 //       return GL_MIRROR_CLAMP_TO_EDGE;

  //  caseGraphicImageWrapRepeat:
  //      return GL_REPEAT;

   // case GraphicImageWrapRepeatAndMirror:
   //     return GL_MIRRORED_REPEAT;
    default:
        return -1;
    }
}

OpenGLID OpenGLToImageLayout(const GraphicImageLayout layout)
{
    switch (layout)
    {
    case GraphicImageLayoutNearest:
        return GL_NEAREST;

    case GraphicImageLayoutLinear:
        return GL_LINEAR;

    case GraphicImageLayoutMipMapNearestNearest:
        return GL_NEAREST_MIPMAP_NEAREST;

    case GraphicImageLayoutMipMapLinearNearest:
        return GL_LINEAR_MIPMAP_NEAREST;

    case GraphicImageLayoutMipMapNNearestLinear:
        return GL_NEAREST_MIPMAP_LINEAR;

    case GraphicImageLayoutMipMapLinearLinear:
        return GL_LINEAR_MIPMAP_LINEAR;

    default:
        return -1;
    }
}















void OpenGLContextSelect(OpenGL* const openGL)
{

}

void OpenGLContextDeselect()
{
#if OSUnix

#elif OSWindows
    wglMakeCurrent(NULL, NULL);
#endif
}

void OpenGLContextRelease(OpenGL* const openGL)
{
#if OSUnix

#elif OSWindows
    const BOOL result = wglDeleteContext(openGL->OpenGLConext);

    if (result)
    {
        openGL->OpenGLConext = 0;
    }

#endif
}

void OpenGLContextFlush()
{
    glFlush(); // Flush drawing command buffer to make drawing happen as soon as possible.
}

OpenGLShaderProgramID OpenGLShaderProgramCreate(OpenGL* const openGL)
{
    return (*openGL->OpenGLShaderProgramCreateCallBack)();
}

void OpenGLShaderProgramUse(OpenGL* const openGL, const OpenGLShaderProgramID shaderProgramID)
{
    (openGL->OpenGLShaderProgramUseCallBack)(shaderProgramID);
}

void OpenGLShaderSource(OpenGL* const openGL, unsigned int shader, int count, const char** string, const int* length)
{
    (openGL->OpenGLShaderSourceCallBack)(shader, count, string, length);
}

void OpenGLShaderCompile(OpenGL* const openGL, const OpenGLShaderID shaderID)
{
    (openGL->OpenGLCompileShaderCallBack)(shaderID);
}

void OpenGLShaderGetiv(OpenGL* const openGL, const OpenGLShaderID shaderID, GLenum pname, GLint* params)
{
    (openGL->OpenGLShaderGetivCallBack)(shaderID, pname, params);
}

void OpenGLShaderLogInfoGet(OpenGL* const openGL, const OpenGLShaderID shaderID, GLsizei maxLength, GLsizei* length, char* infoLog)
{
    (openGL->OpenGLShaderLogInfoGetCallBack)(shaderID, maxLength, length, infoLog);
}

void OpenGLShaderDelete(OpenGL* const openGL, const OpenGLShaderID shaderID)
{
    (openGL->OpenGLShaderDeleteCallBack)(shaderID);
}

void OpenGLVertexAttributeArrayDefine(OpenGL* const openGL, const size_t sizeOfElement, const size_t listSize, const unsigned int* list)
{
    size_t offset = 0;
    size_t wholeBlockSize = 0;
    size_t currentBlockSize = 0;

    for (size_t vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        const unsigned int vertexSize = list[vertexAtributeIndex];

        wholeBlockSize += vertexSize;
    }

    wholeBlockSize *= sizeOfElement;

    for (size_t vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        const unsigned int  vertexSize = list[vertexAtributeIndex];

        //glEnableVertexAttribArray(vertexAtributeIndex);
        //glVertexAttribPointer(vertexAtributeIndex, vertexSize, GL_FLOAT, GL_FALSE, wholeBlockSize, (void*)offset);

        currentBlockSize += vertexSize;
        offset = sizeOfElement * currentBlockSize;
    }
}

void VertexArrayDefine(unsigned int* vertexArrayID)
{
    //glGenVertexArrays(1, vertexArrayID);
}

void VertexDataDefine(unsigned int* vertexID, int size, void* data)
{
    //glGenBuffers(1, vertexID); // Get BufferID
    //glBindBuffer(GL_ARRAY_BUFFER, *vertexID); // Select Buffer
    //glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void IndexDataDefine(unsigned int* indexID, int size, void* data)
{
    //glGenBuffers(1, indexID);
   // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexID);
    //glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void VertexArrayUpdate(int vertexArrayID, int size, void* data)
{
   // glBindVertexArray(vertexArrayID);
   // glBindBuffer(GL_ARRAY_BUFFER, vertexArrayID);
    //glBufferSubData(GL_ARRAY_BUFFER, 0, (GLsizeiptr)size, data);
}

OpenGLID BF::OpenGL::ShaderProgramCreate()
{
    return OpenGLShaderProgramCreate();
}

void BF::OpenGL::DepthMaskEnable(bool enable)
{
    if (enable)
    {
        glDepthMask(GL_TRUE);
    }
    else
    {
        glDepthMask(GL_FALSE);
    }
}

void BF::OpenGL::DrawOrder(bool clockwise)
{
    if (clockwise)
    {
        glFrontFace(GL_CW);
    }
    else
    {
        glFrontFace(GL_CCW);
    }
}

void BF::OpenGL::RenderBothSides(bool renderBothSides)
{
    if (renderBothSides)
    {
        glDisable(GL_CULL_FACE);
    }
    else
    {
        glEnable(GL_CULL_FACE);
    }
}

char BF::OpenGL::UseShaderProgram(int shaderProgramID)
{
    const bool valid = shaderProgramID != -1;

    if(!valid)
    {
        return false;
    }

    glUseProgram(shaderProgramID);

    return true;
}

void BF::OpenGL::VertexArrayBind(int vertexArrayID)
{
    assert(vertexArrayID != -1);

    glBindVertexArray(vertexArrayID);
}

void BF::OpenGL::VertexBufferBind(int vertexBufferID, int indexBuffer)
{
    assert(vertexBufferID != -1);
    assert(indexBuffer != -1);

    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
}

int BF::OpenGL::TextureMaxSlots()
{
    int value = -1;

    glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

int BF::OpenGL::TextureMaxLoaded()
{
    int value = -1;

    glGetIntegerv(GL_MAX_COMBINED_TEXTURE_IMAGE_UNITS, (GLint*)&value);

    return value;
}

const char* BF::OpenGL::GLSLVersionPrimary()
{
    return (const char*)glGetString(GL_SHADING_LANGUAGE_VERSION);
}

void BF::OpenGL::GLSLVersionsSupported(const char*** shaderList, int shaderListSize)
{
    glGetIntegerv(GL_NUM_SHADING_LANGUAGE_VERSIONS, &shaderListSize);

    (*shaderList) = Memory::Allocate<const char*>(shaderListSize);

    for (size_t i = 0; i < shaderListSize; i++)
    {
        const char* shaderVersion = (const char*)glGetStringi(GL_SHADING_LANGUAGE_VERSION, i);

        (*shaderList)[i] = shaderVersion;
    }
}

unsigned int BF::OpenGL::ShaderCompile(unsigned int type, char* shaderString)
{
    unsigned int id = glCreateShader(type);

    glShaderSource(id, 1, &shaderString, nullptr);
    glCompileShader(id);

    // Error handling
    {
        int result;

        glGetShaderiv(id, GL_COMPILE_STATUS, &result);

        if (result == GL_FALSE)
        {
            int lengh = 0;

            glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lengh);
            char* message = Memory::Allocate<char>(lengh);

            glGetShaderInfoLog(id, lengh, &lengh, message);

            printf
            (
                "================================================================================\n"
                "+------------------------------------------------------------------------------+\n"
                "| GLSL - OpenGL Shader - compile error log                                     |\n"
                "+------------------------------------------------------------------------------+\n"
                "%s"
                "+------------------------------------------------------------------------------+\n"
                "================================================================================\n",
                message
            );

            MemoryRelease(message, lengh);

            glDeleteShader(id);

            return -1;
        }
    }

    return id;
}

void BF::OpenGL::VertexAttributeArrayDefine(const unsigned int sizeOfElement, const unsigned int listSize, const unsigned int* list)
{
    int offset = 0;
    int wholeBlockSize = 0;
    int currentBlockSize = 0;

    for (unsigned int vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        int vertexSize = list[vertexAtributeIndex];

        wholeBlockSize += vertexSize;
    }

    wholeBlockSize *= sizeOfElement;

    for (unsigned int vertexAtributeIndex = 0; vertexAtributeIndex < listSize; vertexAtributeIndex++)
    {
        int vertexSize = list[vertexAtributeIndex];

        glEnableVertexAttribArray(vertexAtributeIndex);
        glVertexAttribPointer(vertexAtributeIndex, vertexSize, GL_FLOAT, GL_FALSE, wholeBlockSize, (void*)offset);

        currentBlockSize += vertexSize;
        offset = sizeOfElement * currentBlockSize;
    }
}

void BF::OpenGL::VertexArrayDefine(unsigned int* vertexArrayID)
{
    glGenVertexArrays(1, vertexArrayID);
}

void BF::OpenGL::VertexDataDefine(unsigned int* vertexID, int size, void* data)
{
    glGenBuffers(1, vertexID); // Get BufferID
    glBindBuffer(GL_ARRAY_BUFFER, *vertexID); // Select Buffer
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

void BF::OpenGL::IndexDataDefine(unsigned int* indexID, int size, void* data)
{
    glGenBuffers(1, indexID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *indexID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_DYNAMIC_DRAW);
}

int BF::OpenGL::ShaderGetUniformLocationID(int shaderID, const char* UniformName)
{
    const bool valid = (shaderID != -1) && (UniformName != nullptr);

    if(!valid)
    {
        return -1;
    }

    {
        const int uniformLocationID = glGetUniformLocation(shaderID, UniformName);

        return uniformLocationID;
    }
}

void BF::OpenGL::ShaderSetUniformMatrix4x4(const int matrixUniformID, const float* matrix)
{
    const bool valid = matrixUniformID != -1;

    if (!valid)
    {
        return;
    }

    glUniformMatrix4fv(matrixUniformID, 1, GL_FALSE, matrix);
}

void BF::OpenGL::ShaderSetUniformVector3(int vector3UniformID, float x, float y, float z)
{
    if (vector3UniformID != -1)
    {
        glUniform3f(vector3UniformID, x, y, z);
    }
}

void BF::OpenGL::ShaderSetUniformVector4(int vector3UniformID, float x, float y, float z, float w)
{
    if (vector3UniformID != -1)
    {
        glUniform4f(vector3UniformID, x, y, z, w);
    }
}

#endif


*/

OpenGLShaderProgramID OpenGLShaderProgramCreate(OpenGLContext* const openGLContext)
{
    return openGLContext->OpenGLShaderProgramCreateCallBack();
}

void OpenGLShaderProgramUse(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID)
{
    openGLContext->OpenGLShaderProgramUseCallBack(shaderProgramID);
}

void OpenGLShaderProgramDelete(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID)
{
    openGLContext->OpenGLShaderProgramDeleteCallBack(shaderProgramID);
}

unsigned int OpenGLShaderTypeToID(const OpenGLShaderType openGLShaderType)
{
    switch (openGLShaderType)
    {
    default:
    case OpenGLShaderInvalid:
        return -1;

    case OpenGLShaderVertex:
        return GL_VERTEX_SHADER;

    case OpenGLShaderFragment:
        return GL_FRAGMENT_SHADER;

        // case OpenGLShaderTessellationControl:
        //     return GL_TESS_CONTROL_SHADER;

         //case OpenGLShaderTessellationEvaluation:
        //     return GL_TESS_EVALUATION_SHADER;

    case OpenGLShaderGeometry:
        return GL_GEOMETRY_SHADER;

        // case OpenGLShaderCompute:
       //      return GL_COMPUTE_SHADER;
    }
}

OpenGLShaderID OpenGLShaderCreate(OpenGLContext* const openGLContext, const OpenGLShaderType openGLShaderType)
{
    const unsigned int shaderTypeID = OpenGLShaderTypeToID(openGLShaderType);
    const unsigned int shaderID = openGLContext->OpenGLShaderCreateCallBack(shaderTypeID);

    return shaderID;
}

void OpenGLShaderSource(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, const size_t count, const char** string, size_t* const length)
{
    openGLContext->OpenGLShaderSourceCallBack(shaderID, count, string, length);
}

unsigned char OpenGLShaderCompile(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID)
{
    openGLContext->OpenGLShaderCompileCallBack(shaderID);

    {
        GLint isCompiled = 0;

        OpenGLShaderGetiv(openGLContext, shaderID, GL_COMPILE_STATUS, &isCompiled);

        return isCompiled;
    }
}

void OpenGLShaderGetiv(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, GLenum pname, GLint* params)
{
    openGLContext->OpenGLShaderGetivCallBack(shaderID, pname, params);
}

void OpenGLShaderLogInfoGet(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID, GLsizei maxLength, GLsizei* length, char* infoLog)
{
    openGLContext->OpenGLShaderLogInfoGetCallBack(shaderID, maxLength, length, infoLog);
}

void OpenGLShaderDelete(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID)
{
    openGLContext->OpenGLShaderDeleteCallBack(shaderID);
}

void OpenGLShaderProgramAttach(OpenGLContext* const openGLContext, const OpenGLShaderProgramID shaderProgramID, const OpenGLShaderID shaderID)
{
    openGLContext->OpenGLAttachShaderCallBack(shaderProgramID, shaderID);
}

void OpenGLShaderProgramLink(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID)
{
    openGLContext->OpenGLLinkProgramCallBack(shaderID);
}

void OpenGLShaderProgramValidate(OpenGLContext* const openGLContext, const OpenGLShaderID shaderID)
{
    openGLContext->OpenGLValidateProgramCallBack(shaderID);
}

void OpenGLTextureCreate(OpenGLContext* const openGLContext, GLsizei n, GLuint* textures)
{
    openGLContext->OpenGLTextureCreateCallBack(n, textures);
}

void OpenGLTextureBind(OpenGLContext* const openGLContext, const OpenGLTextureType textureType, GLuint texture)
{
    const unsigned int textureTypeID = OpenGLTextureTypeToID(textureType);

    openGLContext->OpenGLTextureBindCallBack(textureTypeID, texture);
}

void OpenGLTextureDelete(OpenGLContext* const openGLContext, GLsizei n, const GLuint* textures)
{
    openGLContext->OpenGLTextureDeleteCallBack(n, textures);
}

void OpenGLFrameBufferCreate(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const framebufferIDList)
{
    openGLContext->OpenGLFrameBufferCreateCallBack(amount, framebufferIDList);
}

void OpenGLRenderBufferStorage(OpenGLContext* const openGLContext, const OpenGLRenderBufferFormat internalformat, const int width, const int height)
{
    const int internalformatID = OpenGLRenderBufferFormatToID(internalformat);

    openGLContext->OpenGLRenderBufferStorageCallBack(GL_RENDERBUFFER, internalformatID, width, height);
}

void OpenGLFrameBufferBind(OpenGLContext* const openGLContext, const OpenGLFrameBufferMode target, const unsigned int framebufferID)
{
    unsigned int targetID = 0;

    switch (target)
    {
    default:
    case OpenGLFrameBufferModeInvalid:
        targetID = -1;
        break;

    case OpenGLFrameBufferModeDraw:
        targetID = GL_DRAW_FRAMEBUFFER;
        break;

    case OpenGLFrameBufferModeRead:
        targetID = GL_READ_FRAMEBUFFER;
        break;

    case OpenGLFrameBufferModeDrawAndRead:
        targetID = GL_FRAMEBUFFER;
        break;
    }

    openGLContext->OpenGLFrameBufferBindCallBack(targetID, framebufferID); // GL_FRAMEBUFFER
}

void OpenGLFrameBufferDestroy(OpenGLContext* const openGLContext, const unsigned int amount, unsigned int* const framebufferIDList)
{
    openGLContext->OpenGLFrameBufferDeleteCallBack(amount, framebufferIDList);
}

void OpenGLRenderBufferCreate(OpenGLContext* const openGLContext, GLsizei n, GLuint* renderbuffers)
{
    openGLContext->OpenGLRenderBufferCreateCallBack(n, renderbuffers);
}

void OpenGLRenderBufferBind(OpenGLContext* const openGLContext, const unsigned int renderbuffer)
{
    openGLContext->OpenGLRenderBufferBindCallBack(GL_RENDERBUFFER, renderbuffer);
}

void OpenGLRenderBufferDelete(OpenGLContext* const openGLContext, GLsizei n, GLuint* renderbuffers)
{
    openGLContext->OpenGLRenderBufferDeleteCallBack(n, renderbuffers);
}

void OpenGLFrameBufferLinkTexture2D(OpenGLContext* const openGLContext, const OpenGLRenderBufferAttachmentPoint attachment, const OpenGLTextureType textarget, const unsigned int textureID, const int level)
{
    const unsigned int attachmentID = OpenGLRenderBufferAttachmentPointToID(attachment);
    const unsigned int textureTypeID = OpenGLTextureTypeToID(textarget);

    openGLContext->OpenGLFrameBufferLinkTexture2DCallBack(GL_FRAMEBUFFER, attachmentID, textureTypeID, textureID, level);
}

GLuint OpenGLFrameBufferLinkRenderBuffer(OpenGLContext* const openGLContext, const OpenGLRenderBufferAttachmentPoint attachment, const unsigned int renderbuffer)
{
    const unsigned int attachmentID = OpenGLRenderBufferAttachmentPointToID(attachment);

    return openGLContext->OpenGLFrameBufferLinkRenderBufferCallBack(GL_FRAMEBUFFER, attachmentID, GL_RENDERBUFFER, renderbuffer);
}

GLint OpenGLShaderVariableIDGet(OpenGLContext* const openGLContext, GLuint program, const char* name)
{
    return openGLContext->OpenGLGetUniformLocation(program, name);
}

void OpenGLShaderVariableFx1(OpenGLContext* const openGLContext, GLint location, GLfloat v0)
{
    openGLContext->OpenGLUniform1fCallBack(location, v0);
}

void OpenGLShaderVariableFx1xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value)
{
    openGLContext->OpenGLUniform1fvCallBack(location, count, value);
}

void OpenGLShaderVariableIx1(OpenGLContext* const openGLContext, GLint location, GLint v0)
{
    openGLContext->OpenGLUniform1iCallBack(location, v0);
}

void OpenGLShaderVariableIx1xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value)
{
    openGLContext->OpenGLUniform1ivCallBack(location, count, value);
}

void OpenGLShaderVariableFx2(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1)
{
    openGLContext->OpenGLUniform2fCallBack(location, v0, v1);
}

void OpenGLShaderVariableFx2xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value)
{
    openGLContext->OpenGLUniform2fvCallBack(location, count, value);
}

void OpenGLShaderVariableIx2(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1)
{
    openGLContext->OpenGLUniform2iCallBack(location, v0, v1);
}

void OpenGLShaderVariableIx2xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value)
{
    openGLContext->OpenGLUniform2ivCallBack(location, count, value);
}

void OpenGLShaderVariableFx3(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1, GLfloat v2)
{
    openGLContext->OpenGLUniform3fCallBack(location, v0, v1, v2);
}

void OpenGLShaderVariableFx3xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value)
{
    openGLContext->OpenGLUniform3fvCallBack(location, count, value);
}

void OpenGLShaderVariableIx3(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1, GLint v2)
{
    openGLContext->OpenGLUniform3iCallBack(location, v0, v1, v2);
}

void OpenGLShaderVariableIx3xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value)
{
    openGLContext->OpenGLUniform3ivCallBack(location, count, value);
}

void OpenGLShaderVariableFx4(OpenGLContext* const openGLContext, GLint location, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3)
{
    openGLContext->OpenGLUniform4fCallBack(location, v0, v1, v2, v3);
}

void OpenGLShaderVariableFx4xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLfloat* value)
{
    openGLContext->OpenGLUniform4fvCallBack(location, count, value);
}

void OpenGLShaderVariableIx4(OpenGLContext* const openGLContext, GLint location, GLint v0, GLint v1, GLint v2, GLint v3)
{
    openGLContext->OpenGLUniform4iCallBack(location, v0, v1, v2, v3);
}

void OpenGLShaderVariableIx4xN(OpenGLContext* const openGLContext, GLint location, GLsizei count, const GLint* value)
{
    openGLContext->OpenGLUniform4ivCallBack(location, count, value);
}

void OpenGLShaderVariableMatrix2fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    openGLContext->OpenGLUniformMatrix2fvCallBack(location, count, transpose, value);
}

void OpenGLShaderVariableMatrix3fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    openGLContext->OpenGLUniformMatrix3fvCallBack(location, count, transpose, value);
}

void OpenGLShaderVariableMatrix4fv(OpenGLContext* const openGLContext, GLint location, GLsizei count, GLboolean transpose, const GLfloat* value)
{
    openGLContext->OpenGLUniformMatrix4fvCallBack(location, count, transpose, value);
}

void OpenGLPixelDataRead(OpenGLContext* const openGLContext, const int x, const int y, const int width, const int height, OpenGLImageFormat imageFormat, OpenGLDataType openGLDataType, void* const pixelData)
{
    const int imageFormatID = OpenGLImageFormatToID(imageFormat);
    const int dataTypeID = OpenGLDataTypeToID(openGLDataType);

    glReadPixels(x, y, width, height, imageFormatID, dataTypeID, pixelData);
}
