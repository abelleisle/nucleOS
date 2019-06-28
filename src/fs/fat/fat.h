/*
 * @file fat.h
 *
 * Copyright (C) 2019  Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 * Author: Belle-Isle, Andrew <drumsetmonkey@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/**
 * General boot record for all FAT formats.
 */
typedef struct
{
    uint8_t     boot_JMP[3];
    uint8_t     OEM_id[8];
    uint16_t    bytesPerSector;
    uint8_t     sectorsPerCluster;
    uint16_t    amtReservedSectors;
    uint8_t     amtAllocationTables;
    uint16_t    amtDirectoryEntries;
    uint16_t    totalSectorsLV;
    uint8_t     mediaType;
    uint16_t    sectorsPerTable;
    uint16_t    sectorsPerTrack;
    uint16_t    amtHeads;
    uint32_t    amtHiddenSectors;
    uint32_t    amtLargeSectors;
}__attribute__((packed)) nFAT_BS ;

/**
 * Extended boot record for FAT12 + FAT16 formats.
 */
typedef struct
{
    uint8_t     biosDriveNum;
    uint8_t     __reserved;
    uint8_t     signature; // must be 0x28 or 0x29
    uint32_t    volumeID;
    uint8_t     volumeLabel[11];
    uint8_t     FSType[8];

}__attribute__((packed)) nFAT_BS16 ;

/**
 * Extended boot record for FAT32 format.
 */
typedef struct
{
    uint32_t    sectorsPerTable;
    uint16_t    flags;
    uint16_t    FSVersion;
    uint32_t    rootCluster;
    uint16_t    FSInfo;
    uint16_t    backupBootSector;
    uint8_t     __reserved[12]; // once formatted, these should be 0x00
    uint8_t     driveNum;
    uint8_t     __reservedNT;
    uint8_t     signature; // must be 0x28 or 0x29
    uint32_t    bootSignature;
    uint8_t     volumeLabel[11]; // padded with spaces
    uint8_t     FSType[8]; // always "FAT32   ", spec says never trust this
}__attribute__((packed)) nFAT_BS32 ;
