#ifndef INODE_H
#define INODE_H

/** @file inode.h
 * @brief File node and related memory structures.
 */

struct s_inodePointer
{
    uint32 pDirect[12];
    uint32 pSingle;
    uint32 pDouble;
    uint32 pTriple;
};

struct s_inodeDeviceDriver
{
    uint32 pRead;
    uint32 pWrite;
    uint32 pOpen;
    uint32 pClose;
    uint32 pDirRead;
    uint32 pDirFind;
};

/** @brief Inode.
 * Represents a file.
 */
struct s_inode
{
    /** @brief Size in bytes */
    uint32 nSize;
    /** @brief Device specific file id */
    uint32 nDevID;
    /** @brief Owner user ID */
    uint32 nUID;
    /** @brief Owner group ID */
    uint32 nGID;
    /** @brief Access type */
    uint16 nMode;
    /** @brief Last changed time */
    uint32 nCTime;
    /** @brief Last modified time */
    uint32 nMTime;
    /** @brief Last accessed time */
    uint32 nATime;
    /** @brief Number of hard links to this inode */
    uint16 nLinkCount;

    /** @brief Device blocks */
    s_inodePointer* pBlocks;
    /** @brief Number of blocks */
    uint32 nBlockCount;

    /** @brief Device drivers */
    s_inodeDeviceDriver* pDevice;
};

#endif
