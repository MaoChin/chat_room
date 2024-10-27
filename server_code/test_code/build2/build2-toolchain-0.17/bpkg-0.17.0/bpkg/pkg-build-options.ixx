// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
//
// End prologue.

namespace bpkg
{
  // pkg_build_pkg_options
  //

  inline const bool& pkg_build_pkg_options::
  upgrade () const
  {
    return this->upgrade_;
  }

  inline bool& pkg_build_pkg_options::
  upgrade ()
  {
    return this->upgrade_;
  }

  inline void pkg_build_pkg_options::
  upgrade (const bool& x)
  {
    this->upgrade_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  patch () const
  {
    return this->patch_;
  }

  inline bool& pkg_build_pkg_options::
  patch ()
  {
    return this->patch_;
  }

  inline void pkg_build_pkg_options::
  patch (const bool& x)
  {
    this->patch_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  deorphan () const
  {
    return this->deorphan_;
  }

  inline bool& pkg_build_pkg_options::
  deorphan ()
  {
    return this->deorphan_;
  }

  inline void pkg_build_pkg_options::
  deorphan (const bool& x)
  {
    this->deorphan_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  immediate () const
  {
    return this->immediate_;
  }

  inline bool& pkg_build_pkg_options::
  immediate ()
  {
    return this->immediate_;
  }

  inline void pkg_build_pkg_options::
  immediate (const bool& x)
  {
    this->immediate_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  recursive () const
  {
    return this->recursive_;
  }

  inline bool& pkg_build_pkg_options::
  recursive ()
  {
    return this->recursive_;
  }

  inline void pkg_build_pkg_options::
  recursive (const bool& x)
  {
    this->recursive_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  upgrade_immediate () const
  {
    return this->upgrade_immediate_;
  }

  inline bool& pkg_build_pkg_options::
  upgrade_immediate ()
  {
    return this->upgrade_immediate_;
  }

  inline void pkg_build_pkg_options::
  upgrade_immediate (const bool& x)
  {
    this->upgrade_immediate_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  patch_immediate () const
  {
    return this->patch_immediate_;
  }

  inline bool& pkg_build_pkg_options::
  patch_immediate ()
  {
    return this->patch_immediate_;
  }

  inline void pkg_build_pkg_options::
  patch_immediate (const bool& x)
  {
    this->patch_immediate_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  deorphan_immediate () const
  {
    return this->deorphan_immediate_;
  }

  inline bool& pkg_build_pkg_options::
  deorphan_immediate ()
  {
    return this->deorphan_immediate_;
  }

  inline void pkg_build_pkg_options::
  deorphan_immediate (const bool& x)
  {
    this->deorphan_immediate_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  upgrade_recursive () const
  {
    return this->upgrade_recursive_;
  }

  inline bool& pkg_build_pkg_options::
  upgrade_recursive ()
  {
    return this->upgrade_recursive_;
  }

  inline void pkg_build_pkg_options::
  upgrade_recursive (const bool& x)
  {
    this->upgrade_recursive_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  patch_recursive () const
  {
    return this->patch_recursive_;
  }

  inline bool& pkg_build_pkg_options::
  patch_recursive ()
  {
    return this->patch_recursive_;
  }

  inline void pkg_build_pkg_options::
  patch_recursive (const bool& x)
  {
    this->patch_recursive_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  deorphan_recursive () const
  {
    return this->deorphan_recursive_;
  }

  inline bool& pkg_build_pkg_options::
  deorphan_recursive ()
  {
    return this->deorphan_recursive_;
  }

  inline void pkg_build_pkg_options::
  deorphan_recursive (const bool& x)
  {
    this->deorphan_recursive_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  dependency () const
  {
    return this->dependency_;
  }

  inline bool& pkg_build_pkg_options::
  dependency ()
  {
    return this->dependency_;
  }

  inline void pkg_build_pkg_options::
  dependency (const bool& x)
  {
    this->dependency_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  keep_out () const
  {
    return this->keep_out_;
  }

  inline bool& pkg_build_pkg_options::
  keep_out ()
  {
    return this->keep_out_;
  }

  inline void pkg_build_pkg_options::
  keep_out (const bool& x)
  {
    this->keep_out_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  disfigure () const
  {
    return this->disfigure_;
  }

  inline bool& pkg_build_pkg_options::
  disfigure ()
  {
    return this->disfigure_;
  }

  inline void pkg_build_pkg_options::
  disfigure (const bool& x)
  {
    this->disfigure_ = x;
  }

  inline const dir_path& pkg_build_pkg_options::
  checkout_root () const
  {
    return this->checkout_root_;
  }

  inline dir_path& pkg_build_pkg_options::
  checkout_root ()
  {
    return this->checkout_root_;
  }

  inline void pkg_build_pkg_options::
  checkout_root (const dir_path& x)
  {
    this->checkout_root_ = x;
  }

  inline bool pkg_build_pkg_options::
  checkout_root_specified () const
  {
    return this->checkout_root_specified_;
  }

  inline void pkg_build_pkg_options::
  checkout_root_specified (bool x)
  {
    this->checkout_root_specified_ = x;
  }

  inline const bool& pkg_build_pkg_options::
  checkout_purge () const
  {
    return this->checkout_purge_;
  }

  inline bool& pkg_build_pkg_options::
  checkout_purge ()
  {
    return this->checkout_purge_;
  }

  inline void pkg_build_pkg_options::
  checkout_purge (const bool& x)
  {
    this->checkout_purge_ = x;
  }

  inline const strings& pkg_build_pkg_options::
  config_name () const
  {
    return this->config_name_;
  }

  inline strings& pkg_build_pkg_options::
  config_name ()
  {
    return this->config_name_;
  }

  inline void pkg_build_pkg_options::
  config_name (const strings& x)
  {
    this->config_name_ = x;
  }

  inline bool pkg_build_pkg_options::
  config_name_specified () const
  {
    return this->config_name_specified_;
  }

  inline void pkg_build_pkg_options::
  config_name_specified (bool x)
  {
    this->config_name_specified_ = x;
  }

  inline const vector<uint64_t>& pkg_build_pkg_options::
  config_id () const
  {
    return this->config_id_;
  }

  inline vector<uint64_t>& pkg_build_pkg_options::
  config_id ()
  {
    return this->config_id_;
  }

  inline void pkg_build_pkg_options::
  config_id (const vector<uint64_t>& x)
  {
    this->config_id_ = x;
  }

  inline bool pkg_build_pkg_options::
  config_id_specified () const
  {
    return this->config_id_specified_;
  }

  inline void pkg_build_pkg_options::
  config_id_specified (bool x)
  {
    this->config_id_specified_ = x;
  }

  inline const vector<uuid>& pkg_build_pkg_options::
  config_uuid () const
  {
    return this->config_uuid_;
  }

  inline vector<uuid>& pkg_build_pkg_options::
  config_uuid ()
  {
    return this->config_uuid_;
  }

  inline void pkg_build_pkg_options::
  config_uuid (const vector<uuid>& x)
  {
    this->config_uuid_ = x;
  }

  inline bool pkg_build_pkg_options::
  config_uuid_specified () const
  {
    return this->config_uuid_specified_;
  }

  inline void pkg_build_pkg_options::
  config_uuid_specified (bool x)
  {
    this->config_uuid_specified_ = x;
  }

  // pkg_build_options
  //

  inline const bool& pkg_build_options::
  yes () const
  {
    return this->yes_;
  }

  inline bool& pkg_build_options::
  yes ()
  {
    return this->yes_;
  }

  inline void pkg_build_options::
  yes (const bool& x)
  {
    this->yes_ = x;
  }

  inline const string& pkg_build_options::
  for_ () const
  {
    return this->for__;
  }

  inline string& pkg_build_options::
  for_ ()
  {
    return this->for__;
  }

  inline void pkg_build_options::
  for_ (const string& x)
  {
    this->for__ = x;
  }

  inline bool pkg_build_options::
  for__specified () const
  {
    return this->for__specified_;
  }

  inline void pkg_build_options::
  for__specified (bool x)
  {
    this->for__specified_ = x;
  }

  inline const bool& pkg_build_options::
  keep_unused () const
  {
    return this->keep_unused_;
  }

  inline bool& pkg_build_options::
  keep_unused ()
  {
    return this->keep_unused_;
  }

  inline void pkg_build_options::
  keep_unused (const bool& x)
  {
    this->keep_unused_ = x;
  }

  inline const bool& pkg_build_options::
  update_dependent () const
  {
    return this->update_dependent_;
  }

  inline bool& pkg_build_options::
  update_dependent ()
  {
    return this->update_dependent_;
  }

  inline void pkg_build_options::
  update_dependent (const bool& x)
  {
    this->update_dependent_ = x;
  }

  inline const bool& pkg_build_options::
  leave_dependent () const
  {
    return this->leave_dependent_;
  }

  inline bool& pkg_build_options::
  leave_dependent ()
  {
    return this->leave_dependent_;
  }

  inline void pkg_build_options::
  leave_dependent (const bool& x)
  {
    this->leave_dependent_ = x;
  }

  inline const bool& pkg_build_options::
  configure_only () const
  {
    return this->configure_only_;
  }

  inline bool& pkg_build_options::
  configure_only ()
  {
    return this->configure_only_;
  }

  inline void pkg_build_options::
  configure_only (const bool& x)
  {
    this->configure_only_ = x;
  }

  inline const bool& pkg_build_options::
  print_only () const
  {
    return this->print_only_;
  }

  inline bool& pkg_build_options::
  print_only ()
  {
    return this->print_only_;
  }

  inline void pkg_build_options::
  print_only (const bool& x)
  {
    this->print_only_ = x;
  }

  inline const string& pkg_build_options::
  plan () const
  {
    return this->plan_;
  }

  inline string& pkg_build_options::
  plan ()
  {
    return this->plan_;
  }

  inline void pkg_build_options::
  plan (const string& x)
  {
    this->plan_ = x;
  }

  inline bool pkg_build_options::
  plan_specified () const
  {
    return this->plan_specified_;
  }

  inline void pkg_build_options::
  plan_specified (bool x)
  {
    this->plan_specified_ = x;
  }

  inline const bool& pkg_build_options::
  no_fetch () const
  {
    return this->no_fetch_;
  }

  inline bool& pkg_build_options::
  no_fetch ()
  {
    return this->no_fetch_;
  }

  inline void pkg_build_options::
  no_fetch (const bool& x)
  {
    this->no_fetch_ = x;
  }

  inline const bool& pkg_build_options::
  fetch_shallow () const
  {
    return this->fetch_shallow_;
  }

  inline bool& pkg_build_options::
  fetch_shallow ()
  {
    return this->fetch_shallow_;
  }

  inline void pkg_build_options::
  fetch_shallow (const bool& x)
  {
    this->fetch_shallow_ = x;
  }

  inline const strings& pkg_build_options::
  mask_repository () const
  {
    return this->mask_repository_;
  }

  inline strings& pkg_build_options::
  mask_repository ()
  {
    return this->mask_repository_;
  }

  inline void pkg_build_options::
  mask_repository (const strings& x)
  {
    this->mask_repository_ = x;
  }

  inline bool pkg_build_options::
  mask_repository_specified () const
  {
    return this->mask_repository_specified_;
  }

  inline void pkg_build_options::
  mask_repository_specified (bool x)
  {
    this->mask_repository_specified_ = x;
  }

  inline const strings& pkg_build_options::
  mask_repository_uuid () const
  {
    return this->mask_repository_uuid_;
  }

  inline strings& pkg_build_options::
  mask_repository_uuid ()
  {
    return this->mask_repository_uuid_;
  }

  inline void pkg_build_options::
  mask_repository_uuid (const strings& x)
  {
    this->mask_repository_uuid_ = x;
  }

  inline bool pkg_build_options::
  mask_repository_uuid_specified () const
  {
    return this->mask_repository_uuid_specified_;
  }

  inline void pkg_build_options::
  mask_repository_uuid_specified (bool x)
  {
    this->mask_repository_uuid_specified_ = x;
  }

  inline const bool& pkg_build_options::
  no_refinement () const
  {
    return this->no_refinement_;
  }

  inline bool& pkg_build_options::
  no_refinement ()
  {
    return this->no_refinement_;
  }

  inline void pkg_build_options::
  no_refinement (const bool& x)
  {
    this->no_refinement_ = x;
  }

  inline const bool& pkg_build_options::
  no_move () const
  {
    return this->no_move_;
  }

  inline bool& pkg_build_options::
  no_move ()
  {
    return this->no_move_;
  }

  inline void pkg_build_options::
  no_move (const bool& x)
  {
    this->no_move_ = x;
  }

  inline const uint16_t& pkg_build_options::
  noop_exit () const
  {
    return this->noop_exit_;
  }

  inline uint16_t& pkg_build_options::
  noop_exit ()
  {
    return this->noop_exit_;
  }

  inline void pkg_build_options::
  noop_exit (const uint16_t& x)
  {
    this->noop_exit_ = x;
  }

  inline bool pkg_build_options::
  noop_exit_specified () const
  {
    return this->noop_exit_specified_;
  }

  inline void pkg_build_options::
  noop_exit_specified (bool x)
  {
    this->noop_exit_specified_ = x;
  }

  inline const string& pkg_build_options::
  rebuild_checksum () const
  {
    return this->rebuild_checksum_;
  }

  inline string& pkg_build_options::
  rebuild_checksum ()
  {
    return this->rebuild_checksum_;
  }

  inline void pkg_build_options::
  rebuild_checksum (const string& x)
  {
    this->rebuild_checksum_ = x;
  }

  inline bool pkg_build_options::
  rebuild_checksum_specified () const
  {
    return this->rebuild_checksum_specified_;
  }

  inline void pkg_build_options::
  rebuild_checksum_specified (bool x)
  {
    this->rebuild_checksum_specified_ = x;
  }

  inline const uint16_t& pkg_build_options::
  no_private_config () const
  {
    return this->no_private_config_;
  }

  inline uint16_t& pkg_build_options::
  no_private_config ()
  {
    return this->no_private_config_;
  }

  inline void pkg_build_options::
  no_private_config (const uint16_t& x)
  {
    this->no_private_config_ = x;
  }

  inline bool pkg_build_options::
  no_private_config_specified () const
  {
    return this->no_private_config_specified_;
  }

  inline void pkg_build_options::
  no_private_config_specified (bool x)
  {
    this->no_private_config_specified_ = x;
  }

  inline const bool& pkg_build_options::
  sys_no_query () const
  {
    return this->sys_no_query_;
  }

  inline bool& pkg_build_options::
  sys_no_query ()
  {
    return this->sys_no_query_;
  }

  inline void pkg_build_options::
  sys_no_query (const bool& x)
  {
    this->sys_no_query_ = x;
  }

  inline const bool& pkg_build_options::
  sys_install () const
  {
    return this->sys_install_;
  }

  inline bool& pkg_build_options::
  sys_install ()
  {
    return this->sys_install_;
  }

  inline void pkg_build_options::
  sys_install (const bool& x)
  {
    this->sys_install_ = x;
  }

  inline const bool& pkg_build_options::
  sys_no_fetch () const
  {
    return this->sys_no_fetch_;
  }

  inline bool& pkg_build_options::
  sys_no_fetch ()
  {
    return this->sys_no_fetch_;
  }

  inline void pkg_build_options::
  sys_no_fetch (const bool& x)
  {
    this->sys_no_fetch_ = x;
  }

  inline const bool& pkg_build_options::
  sys_no_stub () const
  {
    return this->sys_no_stub_;
  }

  inline bool& pkg_build_options::
  sys_no_stub ()
  {
    return this->sys_no_stub_;
  }

  inline void pkg_build_options::
  sys_no_stub (const bool& x)
  {
    this->sys_no_stub_ = x;
  }

  inline const bool& pkg_build_options::
  sys_yes () const
  {
    return this->sys_yes_;
  }

  inline bool& pkg_build_options::
  sys_yes ()
  {
    return this->sys_yes_;
  }

  inline void pkg_build_options::
  sys_yes (const bool& x)
  {
    this->sys_yes_ = x;
  }

  inline const string& pkg_build_options::
  sys_sudo () const
  {
    return this->sys_sudo_;
  }

  inline string& pkg_build_options::
  sys_sudo ()
  {
    return this->sys_sudo_;
  }

  inline void pkg_build_options::
  sys_sudo (const string& x)
  {
    this->sys_sudo_ = x;
  }

  inline bool pkg_build_options::
  sys_sudo_specified () const
  {
    return this->sys_sudo_specified_;
  }

  inline void pkg_build_options::
  sys_sudo_specified (bool x)
  {
    this->sys_sudo_specified_ = x;
  }

  inline const string& pkg_build_options::
  sys_distribution () const
  {
    return this->sys_distribution_;
  }

  inline string& pkg_build_options::
  sys_distribution ()
  {
    return this->sys_distribution_;
  }

  inline void pkg_build_options::
  sys_distribution (const string& x)
  {
    this->sys_distribution_ = x;
  }

  inline bool pkg_build_options::
  sys_distribution_specified () const
  {
    return this->sys_distribution_specified_;
  }

  inline void pkg_build_options::
  sys_distribution_specified (bool x)
  {
    this->sys_distribution_specified_ = x;
  }

  inline const string& pkg_build_options::
  sys_architecture () const
  {
    return this->sys_architecture_;
  }

  inline string& pkg_build_options::
  sys_architecture ()
  {
    return this->sys_architecture_;
  }

  inline void pkg_build_options::
  sys_architecture (const string& x)
  {
    this->sys_architecture_ = x;
  }

  inline bool pkg_build_options::
  sys_architecture_specified () const
  {
    return this->sys_architecture_specified_;
  }

  inline void pkg_build_options::
  sys_architecture_specified (bool x)
  {
    this->sys_architecture_specified_ = x;
  }

  inline const dir_paths& pkg_build_options::
  directory () const
  {
    return this->directory_;
  }

  inline dir_paths& pkg_build_options::
  directory ()
  {
    return this->directory_;
  }

  inline void pkg_build_options::
  directory (const dir_paths& x)
  {
    this->directory_ = x;
  }

  inline bool pkg_build_options::
  directory_specified () const
  {
    return this->directory_specified_;
  }

  inline void pkg_build_options::
  directory_specified (bool x)
  {
    this->directory_specified_ = x;
  }
}

// Begin epilogue.
//
//
// End epilogue.