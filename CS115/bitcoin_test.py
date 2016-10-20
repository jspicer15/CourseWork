import bitcoinrpc
  
conn = bitcoinrpc.connect_to_remote('foo', 'bar', host='payments.yoyodyne.com', port=8332)
info = conn.getinfo()
print"Blocks: %i" % info.connections
