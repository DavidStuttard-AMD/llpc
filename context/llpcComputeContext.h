/*
 ***********************************************************************************************************************
 *
 *  Copyright (c) 2016-2019 Advanced Micro Devices, Inc. All Rights Reserved.
 *
 *  Permission is hereby granted, free of charge, to any person obtaining a copy
 *  of this software and associated documentation files (the "Software"), to deal
 *  in the Software without restriction, including without limitation the rights
 *  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 *  copies of the Software, and to permit persons to whom the Software is
 *  furnished to do so, subject to the following conditions:
 *
 *  The above copyright notice and this permission notice shall be included in all
 *  copies or substantial portions of the Software.
 *
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 *  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 *  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 *  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 *  SOFTWARE.
 *
 **********************************************************************************************************************/
/**
 ***********************************************************************************************************************
 * @file  llpcComputeContext.h
 * @brief LLPC header file: contains declaration of class Llpc::ComputeContext.
 ***********************************************************************************************************************
 */
#pragma once

#include "llpcPipelineContext.h"

namespace Llpc
{

// =====================================================================================================================
// Represents LLPC context for compute pipeline compilation. Derived from the base class Llpc::Context.
class ComputeContext: public PipelineContext
{
public:
    ComputeContext(GfxIpVersion                    gfxIp,
                   const GpuProperty*              pGpuProp,
                   const WorkaroundFlags*          pGpuWorkarounds,
                   const ComputePipelineBuildInfo* pPipelineInfo,
                   MetroHash::Hash*                pPipelineHash,
                   MetroHash::Hash*                pCacheHash);
    virtual ~ComputeContext() {}

    virtual ResourceUsage* GetShaderResourceUsage(ShaderStage shaderStage);
    virtual InterfaceData* GetShaderInterfaceData(ShaderStage shaderStage);
    virtual const PipelineShaderInfo* GetPipelineShaderInfo(ShaderStage shaderStage) const;

    // Checks whether the pipeline is graphics or compute
    virtual bool IsGraphics() const { return false; }

    // Gets pipeline build info
    virtual const void* GetPipelineBuildInfo() const { return m_pPipelineInfo; }

    // Gets the mask of active shader stages bound to this pipeline
    virtual uint32_t GetShaderStageMask() const { return ShaderStageToMask(ShaderStageCompute); }

    // Gets the count of active shader stages
    virtual uint32_t GetActiveShaderStageCount() const { return 1; }

    // Checks whether tessellation off-chip mode is enabled
    virtual bool IsTessOffChip() const { LLPC_NEVER_CALLED(); return false; }

    // Determines whether GS on-chip mode is valid for this pipeline
    virtual bool CheckGsOnChipValidity() { LLPC_NEVER_CALLED(); return false; }

    // Checks whether GS on-chip mode is enabled
    virtual bool IsGsOnChip() const { LLPC_NEVER_CALLED(); return false; }

    // Enables GS on-chip mode
    virtual void SetGsOnChip(bool gsOnChip) { LLPC_NEVER_CALLED(); }

    // Does user data node merging for all shader stages
    virtual void DoUserDataNodeMerge() { }

#if LLPC_BUILD_GFX10
    // Sets NGG control settings
    virtual void SetNggControl() { LLPC_NEVER_CALLED(); }

    // Gets NGG control settings
    virtual const NggControl* GetNggControl() const { LLPC_NEVER_CALLED(); return nullptr; }

    // Gets WGP mode enablement for the specified shader stage
    virtual bool GetShaderWgpMode(ShaderStage shaderStage) const
    {
        LLPC_ASSERT(shaderStage == ShaderStageCompute);
        return m_pPipelineInfo->cs.options.wgpMode;
    }
#endif

    // Gets float control settings of the specified shader stage for the provide floating-point type.
    virtual FloatControl GetShaderFloatControl(ShaderStage shaderStage, uint32_t bitWidth) const;

    // Gets the count of vertices per primitive
    virtual uint32_t GetVerticesPerPrimitive() const { LLPC_NEVER_CALLED(); return 0; }

    // Gets wave size for the specified shader stage
    virtual uint32_t GetShaderWaveSize(ShaderStage stage);

    // Gets per pipeline options
    virtual const PipelineOptions* GetPipelineOptions() const { return &m_pPipelineInfo->options; }

private:
    LLPC_DISALLOW_DEFAULT_CTOR(ComputeContext);
    LLPC_DISALLOW_COPY_AND_ASSIGN(ComputeContext);

    const ComputePipelineBuildInfo*     m_pPipelineInfo; // Info to build a compute pipeline

    ResourceUsage   m_resUsage;   // Resource usage of compute shader
    InterfaceData   m_intfData;   // Interface data of compute shader
};

} // Llpc
