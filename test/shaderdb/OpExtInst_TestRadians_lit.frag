#version 450

layout(binding = 0) uniform Uniforms
{
    float f1_1;
    vec3 f3_1;
};

layout(location = 0) out vec4 fragColor;

void main()
{
    float f1_0 = radians(f1_1);

    vec3 f3_0 = radians(f3_1);

    fragColor = (f1_0 != f3_0.x) ? vec4(0.5) : vec4(1.0);
}
// BEGIN_SHADERTEST
/*
; RUN: amdllpc -spvgen-dir=%spvgendir% -v %gfxip %s | FileCheck -check-prefix=SHADERTEST %s
; SHADERTEST-LABEL: {{^// LLPC}} SPIRV-to-LLVM translation results
; SHADERTEST: %{{[0-9]*}} = call {{.*}} float @_Z7radiansf(float %{{.*}})
; SHADERTEST: %{{[0-9]*}} = call {{.*}} <3 x float> @_Z7radiansDv3_f(<3 x float> %{{.*}})
; SHADERTEST-LABEL: {{^// LLPC}} pipeline patching results
; SHADERTEST: %{{[0-9]*}} = fmul float %{{.*}}, 0x3F91DF46A0000000
; SHADERTEST: %{{.*}} = fmul float %{{.*}}, 0x3F91DF46A0000000
; SHADERTEST: AMDLLPC SUCCESS
*/
// END_SHADERTEST
