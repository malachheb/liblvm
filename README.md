## Liblvm

liblvm is a rubygem provide functions to manipulate the linux LVM objects.
* Create Lvm 
* Remove LVM
* Get LVM list
* Verify if a LVM exist
* Get vg extent size
* Get vg free size
* Get vg extent count

### Requirement

* libllvm2.7  a linux library

### Getting started

* Install the liblvm rubygem

```ruby
gem  install liblvm
```
* Initialize the lvm Object
Before you should create your VG. The constructor take the VG name as argument

```ruby
lvm = Linuxlvm.new('G5K_VG')
```
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

* Get the lvm version 
```ruby
lvm.get_lvm_version
```
* Get the VG free size (KB)

```ruby
lvm.vg_get_free_size
```

* Get VG extent count

```ruby
lvm.vg_get_extent_count
```

* Get VG extent size

```ruby
lvm.vg_get_extent_size
```

* Get vg free extent count

```ruby
lvm.vg_get_free_extent_count
```

* Create a LV object
the lv_create function take two argument the "lv name" and "lv size"

```ruby
lvm.lv_create("test", lvm.vg_get_extent_size * 10)
```

* Verify if a lv exist

```ruby
lvm.lv_exist("test")
```

* Get the lvs list

```ruby
lvm.get_lv_list
```
* Remove a Lv object

```ruby
lvm.lv_remove("test")
```







