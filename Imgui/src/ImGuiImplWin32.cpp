/*     Copyright 2019 Diligent Graphics LLC
 *  
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 *  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 *  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 *  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF ANY PROPRIETARY RIGHTS.
 *
 *  In no event and under no legal theory, whether in tort (including negligence), 
 *  contract, or otherwise, unless required by applicable law (such as deliberate 
 *  and grossly negligent acts) or agreed to in writing, shall any Contributor be
 *  liable for any damages, including any direct, indirect, special, incidental, 
 *  or consequential damages of any character arising as a result of this License or 
 *  out of the use or inability to use the software (including but not limited to damages 
 *  for loss of goodwill, work stoppage, computer failure or malfunction, or any and 
 *  all other commercial damages or losses), even if such Contributor has been advised 
 *  of the possibility of such damages.
 */

#ifndef NOMINMAX
#   define NOMINMAX
#endif
#include <Windows.h>

#include "imgui.h"
#include "ImGuiImplWin32.h"
#include "examples/imgui_impl_win32.h"

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace Diligent
{

ImGuiImplWin32::ImGuiImplWin32(HWND            hWnd,
                               IRenderDevice*  pDevice,
                               TEXTURE_FORMAT  BackBufferFmt,
                               TEXTURE_FORMAT  DepthBufferFmt,
                               Uint32          InitialVertexBufferSize,
                               Uint32          InitialIndexBufferSize) :
     ImGuiImplDiligent(pDevice, BackBufferFmt, DepthBufferFmt, InitialVertexBufferSize, InitialIndexBufferSize)
{
    ImGui_ImplWin32_Init(hWnd);
}

ImGuiImplWin32::~ImGuiImplWin32()
{
    ImGui_ImplWin32_Shutdown();
}

void ImGuiImplWin32::NewFrame()
{
    ImGui_ImplWin32_NewFrame();
    ImGuiImplDiligent::NewFrame();
}

LRESULT ImGuiImplWin32::Win32_ProcHandler(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    if (ImGui::GetCurrentContext() == NULL)
        return 0;

    auto res = ImGui_ImplWin32_WndProcHandler(hwnd, msg, wParam, lParam);

    ImGuiIO& io = ImGui::GetIO();
    switch (msg)
    {
        case WM_LBUTTONDOWN: case WM_LBUTTONDBLCLK:
        case WM_RBUTTONDOWN: case WM_RBUTTONDBLCLK:
        case WM_MBUTTONDOWN: case WM_MBUTTONDBLCLK:
        case WM_XBUTTONDOWN: case WM_XBUTTONDBLCLK:
        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
        case WM_MBUTTONUP:
        case WM_XBUTTONUP:
        case WM_MOUSEWHEEL:
        case WM_MOUSEHWHEEL:
            return io.WantCaptureMouse ? 1 : 0;

        case WM_KEYDOWN:
        case WM_SYSKEYDOWN:
        case WM_KEYUP:
        case WM_SYSKEYUP:
        case WM_CHAR:
            return io.WantCaptureKeyboard ? 1 : 0;
        case WM_SETCURSOR:
            return res;
    }

    return res;
}

}