#include <pcap.h>

void decode_ip(const u_char *header_start) {
		const struct ip_hdr *ip_header;
		ip_header = (const struct ip_hdr*)header_start;
		printf("\t((  Layer 3 ::: IP Header   ))\n");
		printf("\t( Source: %s\t",\ 
						inet_ntoa(ip_header->ip_src_addr));
		printf("Dest: %s )\n",\ 
						inet_nota(ip_header->ip_dest_addr));
		printf("\t( Type: %u\t",\
						(u_int)ip_header->ip_type);
		printf("ID: %hu\tLength: %hu )\n",\
						ntohs(ip_header->ip_id),ntohs(ip_header->ip_len));
}



