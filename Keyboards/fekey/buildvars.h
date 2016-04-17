/* Copyright (C) 2013-2015 by Jacob Alexander
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#pragma once

// ----- Includes -----



// ----- Defines -----

// You can change these to give your code its own name.
#define STR_MANUFACTURER        L"Kiibohd"
#define STR_PRODUCT             L"Keyboard - fekey PartialMap pjrcUSB full"
#define STR_SERIAL              L"Dirty fekey-wip - 2016-04-15 07:26:03 +0200"


// Strings used in the CLI module
#define CLI_Revision            "f267590f469edb78a4a3f695903e06f14c49c340"
#define CLI_Branch              "fekey-wip"
#define CLI_ModifiedStatus      "Dirty"
#define CLI_ModifiedFiles       "\r\n\tKeyboards/fekey/buildvars.h\r\n\tKeyboards/fekey/generatedKeymap.h\r\n\tKeyboards/fekey/kll_defs.h\r\n\tScan/fekey/defaultMap.kll"
#define CLI_RepoOrigin          "git@github.com:nyaray/controller.git"
#define CLI_CommitDate          "2016-04-15 07:26:03 +0200"
#define CLI_CommitAuthor        "Emilio Nyaray Valenzuela <emilio@nyaray.com>"
#define CLI_Modules             "Scan(fekey) Macro(PartialMap) Output(pjrcUSB) Debug(full)"
#define CLI_BuildDate           "2016-04-17 10:35:07 +0200"
#define CLI_BuildOS             "Darwin-15.0.0"
#define CLI_Arch                "arm"
#define CLI_Chip                "mk20dx256"
#define CLI_CPU                 "cortex-m4"
#define CLI_Device              "Keyboard"


// Mac OS-X and Linux automatically load the correct drivers.  On
// Windows, even though the driver is supplied by Microsoft, an
// INF file is needed to load the driver.  These numbers need to
// match the INF file.
#define VENDOR_ID               0x1C11
#define PRODUCT_ID              0xB04D

