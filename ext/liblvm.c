#include "ruby.h"
#include <lvm2app.h>
#include <string.h>
static VALUE
c_init(VALUE self, VALUE vg)
{
  Check_Type(vg, T_STRING);
  rb_iv_set(self, "@vg", vg);

  return self;
}

static VALUE
c_get_vg(VALUE self)
{
  VALUE vg = rb_iv_get(self, "@vg");
    return vg;
}

static VALUE 
c_set_vg(VALUE self, VALUE vg)
{
  rb_iv_set(self, "@vg", vg);
}

static VALUE
c_get_lvm_version(VALUE self)
{
  char *version;
  version = lvm_library_get_version();
  printf("\n Lvm version : %s \n", version);
}

static VALUE
c_vg_get_free_size(VALUE self)
{
 lvm_t handle;
 vg_t vg_handle;
 VALUE vg = rb_iv_get(self, "@vg");
 char *c_vg = STR2CSTR(vg);
 handle = lvm_init(NULL);
 vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
 uint64_t free_size = lvm_vg_get_free_size(vg_handle);
 lvm_vg_close(vg_handle);
 lvm_quit(handle);
 return INT2NUM(free_size);
}

static VALUE
c_vg_get_extent_size(VALUE self)
{
  lvm_t handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
  uint64_t extent_size = lvm_vg_get_extent_size(vg_handle);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  return INT2NUM(extent_size);
}

static VALUE 
c_vg_get_extent_count(VALUE self)
{
  lvm_t handle;
  vg_t  vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
  uint64_t extent_count = lvm_vg_get_extent_count(vg_handle);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  return INT2NUM(extent_count);
}

static VALUE
c_vg_get_free_extent_count(VALUE self)
{
  lvm_t handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
  uint64_t free_extent_count = lvm_vg_get_free_extent_count(vg_handle);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  return INT2NUM(free_extent_count);
}

static VALUE
c_vg_get_max_lv(VALUE self)
{
  lvm_t handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
  uint64_t max_lv = lvm_vg_get_max_lv(vg_handle);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  return INT2NUM(max_lv);
}

lv_t lvm_lv_from_name(vg_t vg_handle, char *lv_name)
{
 struct dm_list * lv_list = NULL;
 lv_t lv_handle = NULL;
 lv_list_t * lv_list_entry = NULL;
 lv_list = lvm_vg_list_lvs(vg_handle);
 if (lv_list != NULL) {
	dm_list_iterate_items(lv_list_entry, lv_list) {
		const char * lv_name_from_list = lvm_lv_get_name(lv_list_entry->lv);
		if (strcmp(lv_name_from_list, lv_name) == 0) {
			lv_handle = lv_list_entry->lv;
			break;
		}
	}
	}
return lv_handle;
}

static VALUE
c_lv_exist(VALUE self, VALUE lv_name)
{
  lvm_t handle;
  lv_t lv_handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self,"@vg");
  char *c_vg = STR2CSTR(vg);
  char *c_lv_name = STR2CSTR(lv_name);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r" , NULL);
  lv_handle = lvm_lv_from_name(vg_handle, c_lv_name);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  if (lv_handle == NULL)
	return Qfalse;
  else 
	return Qtrue;
} 

static VALUE
c_lv_create(VALUE self, VALUE name, VALUE size)
{
  lvm_t handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  char *c_name = STR2CSTR(name);
  uint64_t c_size = NUM2LONG(size);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "w", NULL);
  lvm_vg_create_lv_linear(vg_handle, c_name, c_size);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
}

static VALUE
c_lv_remove(VALUE self, VALUE name)  
{
  lvm_t handle;
  vg_t vg_handle;
  lv_t lv_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  char *c_name = STR2CSTR(name);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "w", NULL);
  lv_handle = lvm_lv_from_name(vg_handle, c_name);
  int rm = lvm_vg_remove_lv(lv_handle);
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
  if (rm == 0 ) 
  	return Qtrue;
  else 
     	return Qfalse;

}

void
c_get_lv_list(VALUE self)
{
  lvm_t handle;
  vg_t vg_handle;
  VALUE vg = rb_iv_get(self, "@vg");
  char *c_vg = STR2CSTR(vg);
  handle = lvm_init(NULL);
  vg_handle = lvm_vg_open(handle, c_vg, "r", NULL);
  struct dm_list *lvnames;                                                                                                                                       
  struct lvm_lv_list *strl;                                                                                                                                     
  lvnames = lvm_vg_list_lvs(vg_handle);
  printf("\n %s:", c_vg);                                                                                                       
  dm_list_iterate_items(strl, lvnames) {                                                                                                                         
    lv_t lv_handle = strl->lv;
    char *lv_name = lvm_lv_get_name(lv_handle);
    printf ("\n- %s", lv_name);                                                                                                                                      
  }
  lvm_vg_close(vg_handle);
  lvm_quit(handle);
}
 
VALUE cLinuxlvm; 
void Init_liblvm() { 
   cLinuxlvm = rb_define_class("Linuxlvm", rb_cObject);
   rb_define_method(cLinuxlvm, "initialize", c_init, 1);
   rb_define_method(cLinuxlvm, "get_lvm_version", c_get_lvm_version,0); 
   rb_define_method(cLinuxlvm, "get_vg", c_get_vg, 0);
   rb_define_method(cLinuxlvm, "set_vg", c_set_vg, 1);
   rb_define_method(cLinuxlvm, "lv_exist", c_lv_exist, 1);
   rb_define_method(cLinuxlvm, "vg_get_free_size", c_vg_get_free_size, 0);
   rb_define_method(cLinuxlvm, "vg_get_extent_size", c_vg_get_extent_size, 0);
   rb_define_method(cLinuxlvm, "vg_get_extent_count", c_vg_get_extent_count, 0);
   rb_define_method(cLinuxlvm, "vg_get_free_extent_count", c_vg_get_free_extent_count, 0);
   rb_define_method(cLinuxlvm, "vg_get_max_lv", c_vg_get_max_lv, 0);
   rb_define_method(cLinuxlvm, "lv_create", c_lv_create, 2);
   rb_define_method(cLinuxlvm, "lv_remove", c_lv_remove, 1);
   rb_define_method(cLinuxlvm, "get_lv_list", c_get_lv_list, 0);

}
