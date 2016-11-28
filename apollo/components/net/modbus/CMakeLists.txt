


add_library(aw_modbus STATIC 
    netif/aw_mb_ascii.c
	netif/aw_mb_ascii_comm.c
    netif/aw_mb_crc.c
	netif/aw_mb_m_ascii.c
    netif/aw_mb_m_rtu.c
	netif/aw_mb_m_tcp.c
	netif/aw_mb_netif.c
    netif/aw_mb_rtu.c
    netif/aw_mb_tcp.c
	port_aworks/aw_mb_m_portevent.c
    port_aworks/aw_mb_m_portserial.c
	port_aworks/aw_mb_m_porttcp_client.c
	port_aworks/aw_mb_m_porttimer.c
    port_aworks/aw_mb_portevent.c
    port_aworks/aw_mb_portother.c
    port_aworks/aw_mb_portserial.c
    port_aworks/aw_mb_porttcp.c
    port_aworks/aw_mb_porttimer.c
    port_aworks/aw_mb_m_porttimer.c
    master/aw_mb_funcode_fn.c
    master/aw_mb_m_function.c
    master/aw_mb_master.c
    slave/aw_mb_function.c
    slave/aw_mb_regfunction.c
    slave/aw_mb_slave.c
    utility/aw_mb_bits_cp_to_buf.c
    utility/aw_mb_bits_get.c
    utility/aw_mb_bits_set.c
    utility/aw_mb_bits_set_from_buf.c
    utility/aw_mb_regcpy.c
  )
target_include_directories(aw_modbus PUBLIC include )
# need interface aw_common 
target_link_libraries(aw_modbus PUBLIC aworks aw_lwip_1.4.x )

install(TARGETS aw_modbus
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION ${AWORKS_LIB_INSTALL_DIR}
  RUNTIME DESTINATION bin
  )

# install(DIRECTORY config/.
#   DESTINATION include/config
#   )

install(DIRECTORY include/.
  DESTINATION include/
  )
aw_export(aw_modbus)
