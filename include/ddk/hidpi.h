/*
 * Copyright (C) 2015 Aric Stewart
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __HIDPI_H__
#define __HIDPI_H__

typedef enum _HIDP_REPORT_TYPE
{
    HidP_Input,
    HidP_Output,
    HidP_Feature
} HIDP_REPORT_TYPE;

typedef struct _HIDP_BUTTON_CAPS
{
    USAGE    UsagePage;
    UCHAR    ReportID;
    BOOLEAN  IsAlias;
    USHORT   BitField;
    USHORT   LinkCollection;
    USAGE    LinkUsage;
    USAGE    LinkUsagePage;

    BOOLEAN  IsRange;
    BOOLEAN  IsStringRange;
    BOOLEAN  IsDesignatorRange;
    BOOLEAN  IsAbsolute;
    ULONG    Reserved[10];
    union {
        struct {
            USAGE   UsageMin;
            USAGE   UsageMax;
            USHORT  StringMin;
            USHORT  StringMax;
            USHORT  DesignatorMin;
            USHORT  DesignatorMax;
            USHORT  DataIndexMin;
            USHORT  DataIndexMax;
        } Range;
        struct  {
            USAGE   Usage;
            USAGE   Reserved1;
            USHORT  StringIndex;
            USHORT  Reserved2;
            USHORT  DesignatorIndex;
            USHORT  Reserved3;
            USHORT  DataIndex;
            USHORT  Reserved4;
        } NotRange;
    } DUMMYUNIONNAME;
} HIDP_BUTTON_CAPS, *PHIDP_BUTTON_CAPS;

typedef struct _HIDP_VALUE_CAPS
{
    USAGE   UsagePage;
    UCHAR   ReportID;
    BOOLEAN IsAlias;
    USHORT  BitField;
    USHORT  LinkCollection;
    USAGE   LinkUsage;
    USAGE   LinkUsagePage;

    BOOLEAN IsRange;
    BOOLEAN IsStringRange;
    BOOLEAN IsDesignatorRange;
    BOOLEAN IsAbsolute;
    BOOLEAN HasNull;
    UCHAR   Reserved;
    USHORT  BitSize;
    USHORT  ReportCount;
    USHORT  Reserved2[5];
    ULONG   UnitsExp;
    ULONG   Units;
    LONG    LogicalMin;
    LONG    LogicalMax;
    LONG    PhysicalMin;
    LONG    PhysicalMax;
    union {
        struct {
            USAGE   UsageMin;
            USAGE   UsageMax;
            USHORT  StringMin;
            USHORT  StringMax;
            USHORT  DesignatorMin;
            USHORT  DesignatorMax;
            USHORT  DataIndexMin;
            USHORT  DataIndexMax;
        } Range;
        struct {
            USAGE   Usage;
            USAGE   Reserved1;
            USHORT  StringIndex;
            USHORT  Reserved2;
            USHORT  DesignatorIndex;
            USHORT  Reserved3;
            USHORT  DataIndex;
            USHORT  Reserved4;
        } NotRange;
    } DUMMYUNIONNAME;
} HIDP_VALUE_CAPS, *PHIDP_VALUE_CAPS;

typedef struct _HIDP_PREPARSED_DATA * PHIDP_PREPARSED_DATA;

typedef struct _HIDP_CAPS
{
    USAGE   Usage;
    USAGE   UsagePage;
    USHORT  InputReportByteLength;
    USHORT  OutputReportByteLength;
    USHORT  FeatureReportByteLength;
    USHORT  Reserved[17];
    USHORT  NumberLinkCollectionNodes;
    USHORT  NumberInputButtonCaps;
    USHORT  NumberInputValueCaps;
    USHORT  NumberInputDataIndices;
    USHORT  NumberOutputButtonCaps;
    USHORT  NumberOutputValueCaps;
    USHORT  NumberOutputDataIndices;
    USHORT  NumberFeatureButtonCaps;
    USHORT  NumberFeatureValueCaps;
    USHORT  NumberFeatureDataIndices;
} HIDP_CAPS, *PHIDP_CAPS;

NTSTATUS WINAPI HidP_GetButtonCaps(HIDP_REPORT_TYPE ReportType, PHIDP_BUTTON_CAPS ButtonCaps, PUSHORT  ButtonCapsLength, PHIDP_PREPARSED_DATA PreparsedData);
NTSTATUS WINAPI HidP_GetCaps(PHIDP_PREPARSED_DATA PreparsedData, PHIDP_CAPS Capabilities);
NTSTATUS WINAPI HidP_GetUsages(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, PUSAGE UsageList, PULONG UsageLength, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength);
NTSTATUS WINAPI HidP_GetUsageValue(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, USHORT LinkCollection, USAGE Usage, PULONG UsageValue, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength);
NTSTATUS WINAPI HidP_GetValueCaps(HIDP_REPORT_TYPE ReportType, PHIDP_VALUE_CAPS ValueCaps, PUSHORT ValueCapsLength, PHIDP_PREPARSED_DATA PreparsedData);
NTSTATUS WINAPI HidP_InitializeReportForID(HIDP_REPORT_TYPE ReportType, UCHAR ReportID, PHIDP_PREPARSED_DATA PreparsedData, PCHAR Report, ULONG ReportLength);
ULONG WINAPI HidP_MaxUsageListLength(HIDP_REPORT_TYPE ReportType, USAGE UsagePage, PHIDP_PREPARSED_DATA PreparsedData);

#ifndef FACILITY_HID_ERROR_CODE
#define FACILITY_HID_ERROR_CODE 0x11
#endif

#define HIDP_ERROR_CODES(sev, code) ((NTSTATUS)(((sev) << 28) | (FACILITY_HID_ERROR_CODE << 16) | (code)))

#define HIDP_STATUS_SUCCESS                  (HIDP_ERROR_CODES(0x0,0x00))
#define HIDP_STATUS_NULL                     (HIDP_ERROR_CODES(0x8,0x01))
#define HIDP_STATUS_INVALID_PREPARSED_DATA   (HIDP_ERROR_CODES(0xc,0x01))
#define HIDP_STATUS_INVALID_REPORT_TYPE      (HIDP_ERROR_CODES(0xc,0x02))
#define HIDP_STATUS_INVALID_REPORT_LENGTH    (HIDP_ERROR_CODES(0xc,0x03))
#define HIDP_STATUS_USAGE_NOT_FOUND          (HIDP_ERROR_CODES(0xc,0x04))
#define HIDP_STATUS_VALUE_OUT_OF_RANGE       (HIDP_ERROR_CODES(0xc,0x05))
#define HIDP_STATUS_BAD_LOG_PHY_VALUES       (HIDP_ERROR_CODES(0xc,0x06))
#define HIDP_STATUS_BUFFER_TOO_SMALL         (HIDP_ERROR_CODES(0xc,0x07))
#define HIDP_STATUS_INTERNAL_ERROR           (HIDP_ERROR_CODES(0xc,0x08))
#define HIDP_STATUS_I8242_TRANS_UNKNOWN      (HIDP_ERROR_CODES(0xc,0x09))
#define HIDP_STATUS_INCOMPATIBLE_REPORT_ID   (HIDP_ERROR_CODES(0xc,0x0a))
#define HIDP_STATUS_NOT_VALUE_ARRAY          (HIDP_ERROR_CODES(0xc,0x0b))
#define HIDP_STATUS_IS_VALUE_ARRAY           (HIDP_ERROR_CODES(0xc,0x0c))
#define HIDP_STATUS_DATA_INDEX_NOT_FOUND     (HIDP_ERROR_CODES(0xc,0x0d))
#define HIDP_STATUS_DATA_INDEX_OUT_OF_RANGE  (HIDP_ERROR_CODES(0xc,0x0e))
#define HIDP_STATUS_BUTTON_NOT_PRESSED       (HIDP_ERROR_CODES(0xc,0x0f))
#define HIDP_STATUS_REPORT_DOES_NOT_EXIST    (HIDP_ERROR_CODES(0xc,0x10))
#define HIDP_STATUS_NOT_IMPLEMENTED          (HIDP_ERROR_CODES(0xc,0x20))

#endif /* __HIDPI_H__ */