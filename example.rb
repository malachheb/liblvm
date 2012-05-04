require 'rubygems'
require 'liblvm'

lvm = Linuxlvm.new('G5K_VG')

puts lvm.get_lvm_version
puts lvm.vg_get_free_size
puts lvm.vg_get_extent_count
puts lvm.vg_get_extent_size
puts lvm.vg_get_free_extent_count
lvm.lv_create("test", lvm.vg_get_extent_size * 10)
puts lvm.lv_exist("test")
puts lvm.get_lv_list
puts lvm.lv_remove("test")
puts lvm.lv_exist("test")
