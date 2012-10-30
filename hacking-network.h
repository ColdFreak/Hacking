int send_string(int sockfd, unsigned char *buffer) {
		int sent_bytes, bytes_to_send;
		bytes_to_send = strlen(buffer);
		while(bytes_to_send > 0) {
				sent_bytes = send(sockfd, buffer, bytes_to_send, 0);
				if(sent_bytes == -1)
						return 0; // return 0 on send error
				bytes_to_send -= sent_bytes;
				buffer += sent_bytes;
		}
		return 1; // return 1 on success
}

int recv_line(int sockfd, unsigned char *dest_buffer) {
#define	EOL "\r\n"
#define EOL_SIZE 2
		unsigned char *ptr;
		int eol_matched = 0;
		ptr = dest_buffer;

		while(recv(sockfd, ptr, 1, 0) == 1) {
				if(*ptr == EOL[eol_matched]) {
						eol_matched++;
						if(eol_matched == EOL_SIZE) {
								*(ptr+1-EOL_SIZE) = '\0';
								return strlen(dest_buffer);
						}
				}
				else 
						eol_matched = 0;
				ptr++;
		}
		return 0;
}

#define ETHER_ADDR_LEN 6
#define ETHER_HDR_LEN 14

struct ether_hdr {
		unsigned char ether_dest_addr[ETHER_ADDR_LEN]; // Destination MAC address
		unsigned char ether_src_addr[ETHER_ADDR_LEN]; // Source MAC address
		unsigned short ether_type; // Type of Ethernet packet
};

struct ip_hdr {
		unsigned char ip_version_and_header_length; // version and header length combined
		unsigned char ip_tos; 	// type of service
		unsigned short ip_len; 	// total length
		unsigned short ip_id;	// 
		unsigned short ip_frag_offset;
		unsigned char ip_ttl;
		unsigned char ip_type;		// protocol type
		unsigned short ip_checksum;	// checksum
		unsigned int ip_src_addr;	// source IP address
		unsigned int ip_dest_addr;	// destination IP address
};

struct tcp_hdr {
		unsigned short tcp_src_port;
		unsigned short tcp_dest_port;
		unsigned int tcp_seq;
		unsigned int tcp_ack;
		unsigned char reserved:4;	// 4-bits from the 6-bits of reserved space
		unsigned char tcp_offset:4;	// TCP data offset for little endian host
		unsigned char tcp_flags;	// TCP flags(and 2-bits from reserved space)
#define	TCP_FIN		0X01
#define TCP_SYN		0X02
#define TCP_RST		0X04
#define TCP_PUSH	0X08
#define TCP_ACK		0X10
#define TCP_URG		0X20
		unsigned short tcp_window; // TCP window size
		unsigned short tcp_checksum;
		unsigned short tcp_urgent; // TCP urgent pointer
};

