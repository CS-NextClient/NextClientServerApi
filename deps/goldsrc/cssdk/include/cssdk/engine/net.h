/*
 *  Half Life 1 SDK Copyright(c) Valve Corp.
 *
 *  THIS DOCUMENT DESCRIBES A CONTRACT BETWEEN YOU AND VALVE CORPORATION ("Valve").
 *  PLEASE READ IT BEFORE DOWNLOADING OR USING THE HALF LIFE 1 SDK ("SDK"). BY
 *  DOWNLOADING AND/OR USING THE HALF LIFE 1 SDK YOU ACCEPT THIS LICENSE. IF YOU DO
 *  NOT AGREE TO THE TERMS OF THIS LICENSE PLEASE DON'T DOWNLOAD OR USE THE SDK.
 *
 *  You may, free of charge, download and use the SDK to develop a modified Valve
 *  game running on the Half-Life 1 engine. You may distribute your modified Valve
 *  game in source and object code form, but only for free. Terms of use for Valve
 *  games are found in the Steam Subscriber Agreement located here:
 *  http://store.steampowered.com/subscriber_agreement/
 *
 *  You may copy, modify, and distribute the SDK and any modifications you make to
 *  the SDK in source and object code form, but only for free. Any distribution of
 *  this SDK must include this LICENSE file.
 *
 *  Any distribution of the SDK or a substantial portion of the SDK must include
 *  the above copyright notice and the following:
 *
 *    DISCLAIMER OF WARRANTIES. THE HALF LIFE 1 SDK AND ANY OTHER MATERIAL
 *    DOWNLOADED BY LICENSEE IS PROVIDED "AS IS". VALVE AND ITS SUPPLIERS
 *    DISCLAIM ALL WARRANTIES WITH RESPECT TO THE SDK, EITHER EXPRESS OR IMPLIED,
 *    INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY,
 *    NON-INFRINGEMENT, TITLE AND FITNESS FOR A PARTICULAR PURPOSE.
 *
 *    LIMITATION OF LIABILITY. IN NO EVENT SHALL VALVE OR ITS SUPPLIERS BE LIABLE
 *    FOR ANY SPECIAL, INCIDENTAL, INDIRECT, OR CONSEQUENTIAL DAMAGES WHATSOEVER
 *    (INCLUDING, WITHOUT LIMITATION, DAMAGES FOR LOSS OF BUSINESS PROFITS,
 *    BUSINESS INTERRUPTION, LOSS OF BUSINESS INFORMATION, OR ANY OTHER PECUNIARY
 *    LOSS) ARISING OUT OF THE USE OF OR INABILITY TO USE THE ENGINE AND/OR THE
 *    SDK, EVEN IF VALVE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
 *
 *  If you would like to use the SDK for a commercial purpose, please contact Valve
 *  at sourceengine@valvesoftware.com.
 */

#pragma once
// ReSharper disable CppInconsistentNaming

#include <cssdk/common/const.h>
#include <cssdk/common/net_address.h>
#include <cssdk/public/rehlds/common_rehlds.h>

namespace cssdk
{
    /**
     * @brief Net protocol version.
    */
    constexpr auto PROTOCOL_VERSION = 48;

    /**
     * @brief Client connection is initiated by requesting a challenge value the server sends this value back.
    */
    constexpr auto S2C_CHALLENGE = 'A'; // + challenge value

    /**
     * @brief Send a userid, client remote address, is this server secure and engine build number.
    */
    constexpr auto S2C_CONNECTION = 'B';

    /**
     * @brief HLMaster rejected a server's connection because the server needs to be updated.
    */
    constexpr auto M2S_REQUEST_RESTART = 'O';

    /**
     * @brief Response details about each player on the server.
    */
    constexpr auto S2A_PLAYERS = 'D';

    /**
     * @brief Number of rules + string key and string value pairs.
    */
    constexpr auto S2A_RULES = 'E';

    /**
     * @brief Info request.
    */
    constexpr auto S2A_INFO = 'C'; // deprecated goldsrc response

    /**
     * @brief New Query protocol, returns dedicated or not, + other performance info.
    */
    constexpr auto S2A_INFO_DETAILED = 'm';

    /**
     * @brief Send a log event as key value.
    */
    constexpr auto S2A_LOG_STRING = 'R';

    /**
     * @brief Send a log string.
    */
    constexpr auto S2A_LOG_KEY = 'S';

    /**
     * @brief Basic information about the server.
    */
    constexpr auto A2S_INFO = 'T';

    /**
     * @brief Details about each player on the server.
    */
    constexpr auto A2S_PLAYER = 'U';

    /**
     * @brief The rules the server is using.
    */
    constexpr auto A2S_RULES = 'V';

    /**
     * @brief Another user is requesting a challenge value from this machine.
    */
    constexpr auto A2A_GET_CHALLENGE = 'W';

    /**
     * @brief Generic Ping Request.
    */
    constexpr auto A2A_PING = 'i';

    /**
     * @brief Generic Ack.
    */
    constexpr auto A2A_ACK = 'j';

    /**
     * @brief Print to client console.
    */
    constexpr auto A2A_PRINT = 'l';

    /**
     * @brief Challenge response from master.
    */
    constexpr auto M2A_CHALLENGE = 's';

    /**
     * @brief N/D
    */
    constexpr auto MAX_RATE = 100000.F;

    /**
     * @brief N/D
    */
    constexpr auto MIN_RATE = 1000.F;

    /**
     * @brief Default data rate.
    */
    constexpr auto DEFAULT_RATE = 30000.F;

    //
    // Networking info
    //

    /**
     * @brief Max size of udp packet payload.
    */
    constexpr auto MAX_UDP_PACKET = 4010;

    /**
     * @brief Max length of a reliable message.
    */
    constexpr auto MAX_MSG_LEN = 3990;

    /**
     * @brief Max length of unreliable message.
    */
    constexpr auto MAX_DATAGRAM = 4000;

    /**
     * @brief This is the packet payload without any header bytes (which are attached for actual sending).
    */
    constexpr auto NET_MAX_PAYLOAD = 65536;

    /**
     * @brief N/D
    */
    constexpr auto MAX_LATENT = 32;

    /**
     * @brief N/D
    */
    constexpr auto FRAGMENT_C2S_MIN_SIZE = 16;

    /**
     * @brief N/D
    */
    constexpr auto FRAGMENT_S2C_MIN_SIZE = 256;

    /**
     * @brief N/D
    */
    constexpr auto FRAGMENT_S2C_MAX_SIZE = 1024;

    /**
     * @brief N/D
    */
    constexpr auto CLIENT_FRAGMENT_SIZE_ON_CONNECT = 128;

    /**
     * @brief N/D
    */
    constexpr auto CUSTOMIZATION_MAX_SIZE = 20480;

#ifndef REHLDS_FIXES
    /**
     * @brief Size of fragmentation buffer internal buffers.
    */
    constexpr auto FRAGMENT_MAX_SIZE = 1400;

    /**
     * @brief N/D
    */
    constexpr auto MAX_FRAGMENTS = 25000;
#else
    /**
     * @brief N/D
    */
    constexpr auto FRAGMENT_MAX_SIZE = 1024;

    /**
     * @brief Client sends normal fragments only while connecting.
    */
    constexpr auto MAX_NORMAL_FRAGMENTS = NET_MAX_PAYLOAD / CLIENT_FRAGMENT_SIZE_ON_CONNECT;

    /**
     * @brief While client is connecting it sending fragments with minimal size,
     * also it transfers sprays with minimal fragments...
     * But with sv_delayed_spray_upload it sends with cl_dlmax fragment size.
    */
    constexpr auto MAX_FILE_FRAGMENTS = CUSTOMIZATION_MAX_SIZE / FRAGMENT_C2S_MIN_SIZE;
#endif

    /**
     * @brief N/D
    */
    constexpr auto FRAG_NORMAL_STREAM = 0;

    /**
     * @brief N/D
    */
    constexpr auto FRAG_FILE_STREAM = 1;

    /**
     * @brief N/D
    */
    constexpr auto MAX_STREAMS = 2;

    /**
     * @brief N/D
    */
    constexpr auto FLOW_OUTGOING = 0;

    /**
     * @brief N/D
    */
    constexpr auto FLOW_INCOMING = 1;

    /**
     * @brief N/D
    */
    constexpr auto MAX_FLOWS = 2;

    /**
     * @brief Used as array indexer.
    */
    enum class NetSrc
    {
        /**
         * @brief N/D
        */
        Client = 0,

        /**
         * @brief N/D
        */
        Server,

        /**
         * @brief N/D
        */
        Multicast,

        /**
         * @brief N/D
        */
        Max
    };

    /**
     * @brief Message data.
    */
    struct FlowStats
    {
        /**
         * @brief Size of message sent/received.
        */
        int size{};

        /**
         * @brief Time that message was sent/received.
        */
        double time{};
    };

    struct Flow
    {
        /**
         * @brief Data for last MAX_LATENT messages.
        */
        FlowStats stats[MAX_LATENT]{};

        /**
         * @brief Current message position.
        */
        int current{};

        /**
         * @brief Time when we should recompute k/sec data.
        */
        double next_compute{};

        /**
         * @brief N/D
        */
        float kbytes_per_sec{};

        /**
         * @brief N/D
        */
        float avg_kbytes_per_sec{};
    };

    /**
     * @brief Generic fragment structure.
    */
    struct FragBuf
    {
        /**
         * @brief Next buffer in chain.
        */
        FragBuf* next{};

        /**
         * @brief Id of this buffer.
        */
        int buffer_id{};

        /**
         * @brief Message buffer where raw data is stored.
        */
        SizeBuf frag_message{};

        /**
         * @brief The actual data sits here.
        */
        byte frag_message_buf[FRAGMENT_MAX_SIZE]{};

        /**
         * @brief Is this a file buffer?
        */
        qboolean is_file{};

        /**
         * @brief Is this file buffer from memory (custom decal, etc.).
        */
        qboolean is_buffer{};

        /**
         * @brief N/D
        */
        qboolean is_compressed{};

        /**
         * @brief Name of the file to save out on remote host.
        */
        char filename[MAX_RESOURCE_PATH_LENGTH]{};

        /**
         * @brief Offset in file from which to read data.
        */
        int file_offset{};

        /**
         * @brief Size of data to read at that offset.
        */
        int size{};
    };

    /**
     * @brief Waiting list of \c FragBuf chains.
    */
    struct FragBufWaiting
    {
        /**
         * @brief Next chain in waiting list.
        */
        FragBufWaiting* next{};

        /**
         * @brief Number of buffers in this chain.
        */
        int frag_buf_count{};

        /**
         * @brief The actual buffers.
        */
        FragBuf* frag_bufs{};
    };

    /**
     * @brief Network connection channel.
    */
    struct NetChan
    {
        /**
         * @brief N/D
        */
        NetSrc sock{};

        /**
         * @brief Address this channel is talking to.
        */
        NetAddress remote_address{};

        /**
         * @brief N/D
        */
        int player_slot{};

        /**
         * @brief For timeouts. Time last message was received.
        */
        float last_received{};

        /**
         * @brief Time when channel was connected.
        */
        float connect_time{};

        /**
         * @brief Bandwidth choke (bytes per second).
        */
        double rate{};

        /**
         * @brief If real_time > clear_time, free to send next packet.
        */
        double clear_time{};

        //
        // Sequencing variables
        //

        /**
         * @brief Increasing count of sequence numbers.
        */
        int incoming_sequence{};

        /**
         * @brief # of last outgoing message that has been ack'd.
        */
        int incoming_acknowledged{};

        /**
         * @brief Toggles T/F as reliable messages are received.
        */
        int incoming_reliable_acknowledged{};

        /**
         * @brief Single bit, maintained local.
        */
        int incoming_reliable_sequence{};

        /**
         * @brief Message we are sending to remote.
        */
        int outgoing_sequence{};

        /**
         * @brief Whether the message contains reliable payload, single bit.
        */
        int reliable_sequence{};

        /**
         * @brief Outgoing sequence number of last send that had reliable data.
        */
        int last_reliable_sequence{};

        /**
         * @brief N/D
        */
        void* connection_status{};

        /**
         * @brief N/D
        */
        int (*netchan_block_size)(void*){};

        /**
         * @brief Staging and holding areas.
        */
        SizeBuf message{};

        /**
         * @brief N/D
        */
        byte message_buf[MAX_MSG_LEN]{};

        /**
         * @brief Reliable message buffer. We keep adding to it until reliable is acknowledged. Then we clear it.
        */
        int reliable_length{};

        /**
         * @brief N/D
        */
        byte reliable_buf[MAX_MSG_LEN]{};

        /**
         * @brief Waiting list of buffered fragments to go onto queue.
         * Multiple outgoing buffers can be queued in succession.
        */
        FragBufWaiting* wait_list[MAX_STREAMS]{};

        /**
         * @brief Is reliable waiting buf a fragment?
        */
        qboolean reliable_fragment[MAX_STREAMS]{};

        /**
         * @brief Buffer id for each waiting fragment.
        */
        unsigned int reliable_frag_id[MAX_STREAMS]{};

        /**
         * @brief The current fragment being set.
        */
        FragBuf* frag_bufs[MAX_STREAMS]{};

        /**
         * @brief The total number of fragments in this stream.
        */
        int frag_buf_count[MAX_STREAMS]{};

        /**
         * @brief Position in outgoing buffer where frag data starts.
        */
        short int frag_start_pos[MAX_STREAMS]{};

        /**
         * @brief Length of frag data in the buffer.
        */
        short int frag_length[MAX_STREAMS]{};

        /**
         * @brief Incoming fragments are stored here.
        */
        FragBuf* incoming_bufs[MAX_STREAMS]{};

        /**
         * @brief Set to true when incoming data is ready.
        */
        qboolean incoming_ready[MAX_STREAMS]{};

        /**
         * @brief Only referenced by the FRAG_FILE_STREAM component.
         * Name of file being downloaded.
        */
        char incoming_filename[MAX_RESOURCE_PATH_LENGTH]{};

        /**
         * @brief N/D
        */
        void* temp_buffer{};

        /**
         * @brief N/D
        */
        int temp_buffer_size{};

        /**
         * @brief Incoming and outgoing flow metrics.
        */
        Flow flow[MAX_FLOWS]{};
    };
}
