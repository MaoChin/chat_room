// -*- C++ -*-
//
// This file was generated by CLI, a command line interface
// compiler for C++.
//

// Begin prologue.
//
//
// End prologue.

#include <libbuild2/script/builtin-options.hxx>

#include <map>
#include <set>
#include <string>
#include <vector>
#include <utility>
#include <ostream>
#include <sstream>
#include <cstring>

namespace build2
{
  namespace build
  {
    namespace cli
    {
      template <typename X>
      struct parser
      {
        static void
        parse (X& x, bool& xs, scanner& s)
        {
          using namespace std;

          const char* o (s.next ());
          if (s.more ())
          {
            string v (s.next ());
            istringstream is (v);
            if (!(is >> x && is.peek () == istringstream::traits_type::eof ()))
              throw invalid_value (o, v);
          }
          else
            throw missing_value (o);

          xs = true;
        }
      };

      template <>
      struct parser<bool>
      {
        static void
        parse (bool& x, bool& xs, scanner& s)
        {
          const char* o (s.next ());

          if (s.more ())
          {
            const char* v (s.next ());

            if (std::strcmp (v, "1")    == 0 ||
                std::strcmp (v, "true") == 0 ||
                std::strcmp (v, "TRUE") == 0 ||
                std::strcmp (v, "True") == 0)
              x = true;
            else if (std::strcmp (v, "0")     == 0 ||
                     std::strcmp (v, "false") == 0 ||
                     std::strcmp (v, "FALSE") == 0 ||
                     std::strcmp (v, "False") == 0)
              x = false;
            else
              throw invalid_value (o, v);
          }
          else
            throw missing_value (o);

          xs = true;
        }
      };

      template <>
      struct parser<std::string>
      {
        static void
        parse (std::string& x, bool& xs, scanner& s)
        {
          const char* o (s.next ());

          if (s.more ())
            x = s.next ();
          else
            throw missing_value (o);

          xs = true;
        }
      };

      template <typename X>
      struct parser<std::pair<X, std::size_t> >
      {
        static void
        parse (std::pair<X, std::size_t>& x, bool& xs, scanner& s)
        {
          x.second = s.position ();
          parser<X>::parse (x.first, xs, s);
        }
      };

      template <typename X>
      struct parser<std::vector<X> >
      {
        static void
        parse (std::vector<X>& c, bool& xs, scanner& s)
        {
          X x;
          bool dummy;
          parser<X>::parse (x, dummy, s);
          c.push_back (x);
          xs = true;
        }
      };

      template <typename X, typename C>
      struct parser<std::set<X, C> >
      {
        static void
        parse (std::set<X, C>& c, bool& xs, scanner& s)
        {
          X x;
          bool dummy;
          parser<X>::parse (x, dummy, s);
          c.insert (x);
          xs = true;
        }
      };

      template <typename K, typename V, typename C>
      struct parser<std::map<K, V, C> >
      {
        static void
        parse (std::map<K, V, C>& m, bool& xs, scanner& s)
        {
          const char* o (s.next ());

          if (s.more ())
          {
            std::size_t pos (s.position ());
            std::string ov (s.next ());
            std::string::size_type p = ov.find ('=');

            K k = K ();
            V v = V ();
            std::string kstr (ov, 0, p);
            std::string vstr (ov, (p != std::string::npos ? p + 1 : ov.size ()));

            int ac (2);
            char* av[] =
            {
              const_cast<char*> (o),
              0
            };

            bool dummy;
            if (!kstr.empty ())
            {
              av[1] = const_cast<char*> (kstr.c_str ());
              argv_scanner s (0, ac, av, false, pos);
              parser<K>::parse (k, dummy, s);
            }

            if (!vstr.empty ())
            {
              av[1] = const_cast<char*> (vstr.c_str ());
              argv_scanner s (0, ac, av, false, pos);
              parser<V>::parse (v, dummy, s);
            }

            m[k] = v;
          }
          else
            throw missing_value (o);

          xs = true;
        }
      };

      template <typename K, typename V, typename C>
      struct parser<std::multimap<K, V, C> >
      {
        static void
        parse (std::multimap<K, V, C>& m, bool& xs, scanner& s)
        {
          const char* o (s.next ());

          if (s.more ())
          {
            std::size_t pos (s.position ());
            std::string ov (s.next ());
            std::string::size_type p = ov.find ('=');

            K k = K ();
            V v = V ();
            std::string kstr (ov, 0, p);
            std::string vstr (ov, (p != std::string::npos ? p + 1 : ov.size ()));

            int ac (2);
            char* av[] =
            {
              const_cast<char*> (o),
              0
            };

            bool dummy;
            if (!kstr.empty ())
            {
              av[1] = const_cast<char*> (kstr.c_str ());
              argv_scanner s (0, ac, av, false, pos);
              parser<K>::parse (k, dummy, s);
            }

            if (!vstr.empty ())
            {
              av[1] = const_cast<char*> (vstr.c_str ());
              argv_scanner s (0, ac, av, false, pos);
              parser<V>::parse (v, dummy, s);
            }

            m.insert (typename std::multimap<K, V, C>::value_type (k, v));
          }
          else
            throw missing_value (o);

          xs = true;
        }
      };

      template <typename X, typename T, T X::*M>
      void
      thunk (X& x, scanner& s)
      {
        parser<T>::parse (x.*M, s);
      }

      template <typename X, bool X::*M>
      void
      thunk (X& x, scanner& s)
      {
        s.next ();
        x.*M = true;
      }

      template <typename X, typename T, T X::*M, bool X::*S>
      void
      thunk (X& x, scanner& s)
      {
        parser<T>::parse (x.*M, x.*S, s);
      }
    }
  }
}

#include <map>

namespace build2
{
  namespace script
  {
    // set_options
    //

    set_options::
    set_options ()
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
    }

    set_options::
    set_options (int& argc,
                 char** argv,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
    }

    set_options::
    set_options (int start,
                 int& argc,
                 char** argv,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
    }

    set_options::
    set_options (int& argc,
                 char** argv,
                 int& end,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    set_options::
    set_options (int start,
                 int& argc,
                 char** argv,
                 int& end,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    set_options::
    set_options (::build2::build::cli::scanner& s,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      _parse (s, opt, arg);
    }

    typedef
    std::map<std::string, void (*) (set_options&, ::build2::build::cli::scanner&)>
    _cli_set_options_map;

    static _cli_set_options_map _cli_set_options_map_;

    struct _cli_set_options_map_init
    {
      _cli_set_options_map_init ()
      {
        _cli_set_options_map_["--exact"] =
        &::build2::build::cli::thunk< set_options, &set_options::exact_ >;
        _cli_set_options_map_["-e"] =
        &::build2::build::cli::thunk< set_options, &set_options::exact_ >;
        _cli_set_options_map_["--newline"] =
        &::build2::build::cli::thunk< set_options, &set_options::newline_ >;
        _cli_set_options_map_["-n"] =
        &::build2::build::cli::thunk< set_options, &set_options::newline_ >;
        _cli_set_options_map_["--whitespace"] =
        &::build2::build::cli::thunk< set_options, &set_options::whitespace_ >;
        _cli_set_options_map_["-w"] =
        &::build2::build::cli::thunk< set_options, &set_options::whitespace_ >;
      }
    };

    static _cli_set_options_map_init _cli_set_options_map_init_;

    bool set_options::
    _parse (const char* o, ::build2::build::cli::scanner& s)
    {
      _cli_set_options_map::const_iterator i (_cli_set_options_map_.find (o));

      if (i != _cli_set_options_map_.end ())
      {
        (*(i->second)) (*this, s);
        return true;
      }

      return false;
    }

    bool set_options::
    _parse (::build2::build::cli::scanner& s,
            ::build2::build::cli::unknown_mode opt_mode,
            ::build2::build::cli::unknown_mode arg_mode)
    {
      // Can't skip combined flags (--no-combined-flags).
      //
      assert (opt_mode != ::build2::build::cli::unknown_mode::skip);

      bool r = false;
      bool opt = true;

      while (s.more ())
      {
        const char* o = s.peek ();

        if (std::strcmp (o, "--") == 0)
        {
          opt = false;
          s.skip ();
          r = true;
          continue;
        }

        if (opt)
        {
          if (_parse (o, s))
          {
            r = true;
            continue;
          }

          if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
          {
            // Handle combined option values.
            //
            std::string co;
            if (const char* v = std::strchr (o, '='))
            {
              co.assign (o, 0, v - o);
              ++v;

              int ac (2);
              char* av[] =
              {
                const_cast<char*> (co.c_str ()),
                const_cast<char*> (v)
              };

              ::build2::build::cli::argv_scanner ns (0, ac, av);

              if (_parse (co.c_str (), ns))
              {
                // Parsed the option but not its value?
                //
                if (ns.end () != 2)
                  throw ::build2::build::cli::invalid_value (co, v);

                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = co.c_str ();
              }
            }

            // Handle combined flags.
            //
            char cf[3];
            {
              const char* p = o + 1;
              for (; *p != '\0'; ++p)
              {
                if (!((*p >= 'a' && *p <= 'z') ||
                      (*p >= 'A' && *p <= 'Z') ||
                      (*p >= '0' && *p <= '9')))
                  break;
              }

              if (*p == '\0')
              {
                for (p = o + 1; *p != '\0'; ++p)
                {
                  std::strcpy (cf, "-");
                  cf[1] = *p;
                  cf[2] = '\0';

                  int ac (1);
                  char* av[] =
                  {
                    cf
                  };

                  ::build2::build::cli::argv_scanner ns (0, ac, av);

                  if (!_parse (cf, ns))
                    break;
                }

                if (*p == '\0')
                {
                  // All handled.
                  //
                  s.next ();
                  r = true;
                  continue;
                }
                else
                {
                  // Set the unknown option and fall through.
                  //
                  o = cf;
                }
              }
            }

            switch (opt_mode)
            {
              case ::build2::build::cli::unknown_mode::skip:
              {
                s.skip ();
                r = true;
                continue;
              }
              case ::build2::build::cli::unknown_mode::stop:
              {
                break;
              }
              case ::build2::build::cli::unknown_mode::fail:
              {
                throw ::build2::build::cli::unknown_option (o);
              }
            }

            break;
          }
        }

        switch (arg_mode)
        {
          case ::build2::build::cli::unknown_mode::skip:
          {
            s.skip ();
            r = true;
            continue;
          }
          case ::build2::build::cli::unknown_mode::stop:
          {
            break;
          }
          case ::build2::build::cli::unknown_mode::fail:
          {
            throw ::build2::build::cli::unknown_argument (o);
          }
        }

        break;
      }

      return r;
    }

    // timeout_options
    //

    timeout_options::
    timeout_options ()
    : success_ ()
    {
    }

    timeout_options::
    timeout_options (int& argc,
                     char** argv,
                     bool erase,
                     ::build2::build::cli::unknown_mode opt,
                     ::build2::build::cli::unknown_mode arg)
    : success_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
    }

    timeout_options::
    timeout_options (int start,
                     int& argc,
                     char** argv,
                     bool erase,
                     ::build2::build::cli::unknown_mode opt,
                     ::build2::build::cli::unknown_mode arg)
    : success_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
    }

    timeout_options::
    timeout_options (int& argc,
                     char** argv,
                     int& end,
                     bool erase,
                     ::build2::build::cli::unknown_mode opt,
                     ::build2::build::cli::unknown_mode arg)
    : success_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    timeout_options::
    timeout_options (int start,
                     int& argc,
                     char** argv,
                     int& end,
                     bool erase,
                     ::build2::build::cli::unknown_mode opt,
                     ::build2::build::cli::unknown_mode arg)
    : success_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    timeout_options::
    timeout_options (::build2::build::cli::scanner& s,
                     ::build2::build::cli::unknown_mode opt,
                     ::build2::build::cli::unknown_mode arg)
    : success_ ()
    {
      _parse (s, opt, arg);
    }

    typedef
    std::map<std::string, void (*) (timeout_options&, ::build2::build::cli::scanner&)>
    _cli_timeout_options_map;

    static _cli_timeout_options_map _cli_timeout_options_map_;

    struct _cli_timeout_options_map_init
    {
      _cli_timeout_options_map_init ()
      {
        _cli_timeout_options_map_["--success"] =
        &::build2::build::cli::thunk< timeout_options, &timeout_options::success_ >;
        _cli_timeout_options_map_["-s"] =
        &::build2::build::cli::thunk< timeout_options, &timeout_options::success_ >;
      }
    };

    static _cli_timeout_options_map_init _cli_timeout_options_map_init_;

    bool timeout_options::
    _parse (const char* o, ::build2::build::cli::scanner& s)
    {
      _cli_timeout_options_map::const_iterator i (_cli_timeout_options_map_.find (o));

      if (i != _cli_timeout_options_map_.end ())
      {
        (*(i->second)) (*this, s);
        return true;
      }

      return false;
    }

    bool timeout_options::
    _parse (::build2::build::cli::scanner& s,
            ::build2::build::cli::unknown_mode opt_mode,
            ::build2::build::cli::unknown_mode arg_mode)
    {
      // Can't skip combined flags (--no-combined-flags).
      //
      assert (opt_mode != ::build2::build::cli::unknown_mode::skip);

      bool r = false;
      bool opt = true;

      while (s.more ())
      {
        const char* o = s.peek ();

        if (std::strcmp (o, "--") == 0)
        {
          opt = false;
          s.skip ();
          r = true;
          continue;
        }

        if (opt)
        {
          if (_parse (o, s))
          {
            r = true;
            continue;
          }

          if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
          {
            // Handle combined option values.
            //
            std::string co;
            if (const char* v = std::strchr (o, '='))
            {
              co.assign (o, 0, v - o);
              ++v;

              int ac (2);
              char* av[] =
              {
                const_cast<char*> (co.c_str ()),
                const_cast<char*> (v)
              };

              ::build2::build::cli::argv_scanner ns (0, ac, av);

              if (_parse (co.c_str (), ns))
              {
                // Parsed the option but not its value?
                //
                if (ns.end () != 2)
                  throw ::build2::build::cli::invalid_value (co, v);

                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = co.c_str ();
              }
            }

            // Handle combined flags.
            //
            char cf[3];
            {
              const char* p = o + 1;
              for (; *p != '\0'; ++p)
              {
                if (!((*p >= 'a' && *p <= 'z') ||
                      (*p >= 'A' && *p <= 'Z') ||
                      (*p >= '0' && *p <= '9')))
                  break;
              }

              if (*p == '\0')
              {
                for (p = o + 1; *p != '\0'; ++p)
                {
                  std::strcpy (cf, "-");
                  cf[1] = *p;
                  cf[2] = '\0';

                  int ac (1);
                  char* av[] =
                  {
                    cf
                  };

                  ::build2::build::cli::argv_scanner ns (0, ac, av);

                  if (!_parse (cf, ns))
                    break;
                }

                if (*p == '\0')
                {
                  // All handled.
                  //
                  s.next ();
                  r = true;
                  continue;
                }
                else
                {
                  // Set the unknown option and fall through.
                  //
                  o = cf;
                }
              }
            }

            switch (opt_mode)
            {
              case ::build2::build::cli::unknown_mode::skip:
              {
                s.skip ();
                r = true;
                continue;
              }
              case ::build2::build::cli::unknown_mode::stop:
              {
                break;
              }
              case ::build2::build::cli::unknown_mode::fail:
              {
                throw ::build2::build::cli::unknown_option (o);
              }
            }

            break;
          }
        }

        switch (arg_mode)
        {
          case ::build2::build::cli::unknown_mode::skip:
          {
            s.skip ();
            r = true;
            continue;
          }
          case ::build2::build::cli::unknown_mode::stop:
          {
            break;
          }
          case ::build2::build::cli::unknown_mode::fail:
          {
            throw ::build2::build::cli::unknown_argument (o);
          }
        }

        break;
      }

      return r;
    }

    // export_options
    //

    export_options::
    export_options ()
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
    }

    export_options::
    export_options (int& argc,
                    char** argv,
                    bool erase,
                    ::build2::build::cli::unknown_mode opt,
                    ::build2::build::cli::unknown_mode arg)
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
    }

    export_options::
    export_options (int start,
                    int& argc,
                    char** argv,
                    bool erase,
                    ::build2::build::cli::unknown_mode opt,
                    ::build2::build::cli::unknown_mode arg)
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
    }

    export_options::
    export_options (int& argc,
                    char** argv,
                    int& end,
                    bool erase,
                    ::build2::build::cli::unknown_mode opt,
                    ::build2::build::cli::unknown_mode arg)
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    export_options::
    export_options (int start,
                    int& argc,
                    char** argv,
                    int& end,
                    bool erase,
                    ::build2::build::cli::unknown_mode opt,
                    ::build2::build::cli::unknown_mode arg)
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    export_options::
    export_options (::build2::build::cli::scanner& s,
                    ::build2::build::cli::unknown_mode opt,
                    ::build2::build::cli::unknown_mode arg)
    : unset_ (),
      unset_specified_ (false),
      clear_ (),
      clear_specified_ (false)
    {
      _parse (s, opt, arg);
    }

    typedef
    std::map<std::string, void (*) (export_options&, ::build2::build::cli::scanner&)>
    _cli_export_options_map;

    static _cli_export_options_map _cli_export_options_map_;

    struct _cli_export_options_map_init
    {
      _cli_export_options_map_init ()
      {
        _cli_export_options_map_["--unset"] =
        &::build2::build::cli::thunk< export_options, vector<string>, &export_options::unset_,
          &export_options::unset_specified_ >;
        _cli_export_options_map_["-u"] =
        &::build2::build::cli::thunk< export_options, vector<string>, &export_options::unset_,
          &export_options::unset_specified_ >;
        _cli_export_options_map_["--clear"] =
        &::build2::build::cli::thunk< export_options, vector<string>, &export_options::clear_,
          &export_options::clear_specified_ >;
        _cli_export_options_map_["-c"] =
        &::build2::build::cli::thunk< export_options, vector<string>, &export_options::clear_,
          &export_options::clear_specified_ >;
      }
    };

    static _cli_export_options_map_init _cli_export_options_map_init_;

    bool export_options::
    _parse (const char* o, ::build2::build::cli::scanner& s)
    {
      _cli_export_options_map::const_iterator i (_cli_export_options_map_.find (o));

      if (i != _cli_export_options_map_.end ())
      {
        (*(i->second)) (*this, s);
        return true;
      }

      return false;
    }

    bool export_options::
    _parse (::build2::build::cli::scanner& s,
            ::build2::build::cli::unknown_mode opt_mode,
            ::build2::build::cli::unknown_mode arg_mode)
    {
      // Can't skip combined flags (--no-combined-flags).
      //
      assert (opt_mode != ::build2::build::cli::unknown_mode::skip);

      bool r = false;
      bool opt = true;

      while (s.more ())
      {
        const char* o = s.peek ();

        if (std::strcmp (o, "--") == 0)
        {
          opt = false;
          s.skip ();
          r = true;
          continue;
        }

        if (opt)
        {
          if (_parse (o, s))
          {
            r = true;
            continue;
          }

          if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
          {
            // Handle combined option values.
            //
            std::string co;
            if (const char* v = std::strchr (o, '='))
            {
              co.assign (o, 0, v - o);
              ++v;

              int ac (2);
              char* av[] =
              {
                const_cast<char*> (co.c_str ()),
                const_cast<char*> (v)
              };

              ::build2::build::cli::argv_scanner ns (0, ac, av);

              if (_parse (co.c_str (), ns))
              {
                // Parsed the option but not its value?
                //
                if (ns.end () != 2)
                  throw ::build2::build::cli::invalid_value (co, v);

                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = co.c_str ();
              }
            }

            // Handle combined flags.
            //
            char cf[3];
            {
              const char* p = o + 1;
              for (; *p != '\0'; ++p)
              {
                if (!((*p >= 'a' && *p <= 'z') ||
                      (*p >= 'A' && *p <= 'Z') ||
                      (*p >= '0' && *p <= '9')))
                  break;
              }

              if (*p == '\0')
              {
                for (p = o + 1; *p != '\0'; ++p)
                {
                  std::strcpy (cf, "-");
                  cf[1] = *p;
                  cf[2] = '\0';

                  int ac (1);
                  char* av[] =
                  {
                    cf
                  };

                  ::build2::build::cli::argv_scanner ns (0, ac, av);

                  if (!_parse (cf, ns))
                    break;
                }

                if (*p == '\0')
                {
                  // All handled.
                  //
                  s.next ();
                  r = true;
                  continue;
                }
                else
                {
                  // Set the unknown option and fall through.
                  //
                  o = cf;
                }
              }
            }

            switch (opt_mode)
            {
              case ::build2::build::cli::unknown_mode::skip:
              {
                s.skip ();
                r = true;
                continue;
              }
              case ::build2::build::cli::unknown_mode::stop:
              {
                break;
              }
              case ::build2::build::cli::unknown_mode::fail:
              {
                throw ::build2::build::cli::unknown_option (o);
              }
            }

            break;
          }
        }

        switch (arg_mode)
        {
          case ::build2::build::cli::unknown_mode::skip:
          {
            s.skip ();
            r = true;
            continue;
          }
          case ::build2::build::cli::unknown_mode::stop:
          {
            break;
          }
          case ::build2::build::cli::unknown_mode::fail:
          {
            throw ::build2::build::cli::unknown_argument (o);
          }
        }

        break;
      }

      return r;
    }

    // for_options
    //

    for_options::
    for_options ()
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
    }

    for_options::
    for_options (int& argc,
                 char** argv,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
    }

    for_options::
    for_options (int start,
                 int& argc,
                 char** argv,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
    }

    for_options::
    for_options (int& argc,
                 char** argv,
                 int& end,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    for_options::
    for_options (int start,
                 int& argc,
                 char** argv,
                 int& end,
                 bool erase,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      ::build2::build::cli::argv_scanner s (start, argc, argv, erase);
      _parse (s, opt, arg);
      end = s.end ();
    }

    for_options::
    for_options (::build2::build::cli::scanner& s,
                 ::build2::build::cli::unknown_mode opt,
                 ::build2::build::cli::unknown_mode arg)
    : exact_ (),
      newline_ (),
      whitespace_ ()
    {
      _parse (s, opt, arg);
    }

    typedef
    std::map<std::string, void (*) (for_options&, ::build2::build::cli::scanner&)>
    _cli_for_options_map;

    static _cli_for_options_map _cli_for_options_map_;

    struct _cli_for_options_map_init
    {
      _cli_for_options_map_init ()
      {
        _cli_for_options_map_["--exact"] =
        &::build2::build::cli::thunk< for_options, &for_options::exact_ >;
        _cli_for_options_map_["-e"] =
        &::build2::build::cli::thunk< for_options, &for_options::exact_ >;
        _cli_for_options_map_["--newline"] =
        &::build2::build::cli::thunk< for_options, &for_options::newline_ >;
        _cli_for_options_map_["-n"] =
        &::build2::build::cli::thunk< for_options, &for_options::newline_ >;
        _cli_for_options_map_["--whitespace"] =
        &::build2::build::cli::thunk< for_options, &for_options::whitespace_ >;
        _cli_for_options_map_["-w"] =
        &::build2::build::cli::thunk< for_options, &for_options::whitespace_ >;
      }
    };

    static _cli_for_options_map_init _cli_for_options_map_init_;

    bool for_options::
    _parse (const char* o, ::build2::build::cli::scanner& s)
    {
      _cli_for_options_map::const_iterator i (_cli_for_options_map_.find (o));

      if (i != _cli_for_options_map_.end ())
      {
        (*(i->second)) (*this, s);
        return true;
      }

      return false;
    }

    bool for_options::
    _parse (::build2::build::cli::scanner& s,
            ::build2::build::cli::unknown_mode opt_mode,
            ::build2::build::cli::unknown_mode arg_mode)
    {
      // Can't skip combined flags (--no-combined-flags).
      //
      assert (opt_mode != ::build2::build::cli::unknown_mode::skip);

      bool r = false;
      bool opt = true;

      while (s.more ())
      {
        const char* o = s.peek ();

        if (std::strcmp (o, "--") == 0)
        {
          opt = false;
          s.skip ();
          r = true;
          continue;
        }

        if (opt)
        {
          if (_parse (o, s))
          {
            r = true;
            continue;
          }

          if (std::strncmp (o, "-", 1) == 0 && o[1] != '\0')
          {
            // Handle combined option values.
            //
            std::string co;
            if (const char* v = std::strchr (o, '='))
            {
              co.assign (o, 0, v - o);
              ++v;

              int ac (2);
              char* av[] =
              {
                const_cast<char*> (co.c_str ()),
                const_cast<char*> (v)
              };

              ::build2::build::cli::argv_scanner ns (0, ac, av);

              if (_parse (co.c_str (), ns))
              {
                // Parsed the option but not its value?
                //
                if (ns.end () != 2)
                  throw ::build2::build::cli::invalid_value (co, v);

                s.next ();
                r = true;
                continue;
              }
              else
              {
                // Set the unknown option and fall through.
                //
                o = co.c_str ();
              }
            }

            // Handle combined flags.
            //
            char cf[3];
            {
              const char* p = o + 1;
              for (; *p != '\0'; ++p)
              {
                if (!((*p >= 'a' && *p <= 'z') ||
                      (*p >= 'A' && *p <= 'Z') ||
                      (*p >= '0' && *p <= '9')))
                  break;
              }

              if (*p == '\0')
              {
                for (p = o + 1; *p != '\0'; ++p)
                {
                  std::strcpy (cf, "-");
                  cf[1] = *p;
                  cf[2] = '\0';

                  int ac (1);
                  char* av[] =
                  {
                    cf
                  };

                  ::build2::build::cli::argv_scanner ns (0, ac, av);

                  if (!_parse (cf, ns))
                    break;
                }

                if (*p == '\0')
                {
                  // All handled.
                  //
                  s.next ();
                  r = true;
                  continue;
                }
                else
                {
                  // Set the unknown option and fall through.
                  //
                  o = cf;
                }
              }
            }

            switch (opt_mode)
            {
              case ::build2::build::cli::unknown_mode::skip:
              {
                s.skip ();
                r = true;
                continue;
              }
              case ::build2::build::cli::unknown_mode::stop:
              {
                break;
              }
              case ::build2::build::cli::unknown_mode::fail:
              {
                throw ::build2::build::cli::unknown_option (o);
              }
            }

            break;
          }
        }

        switch (arg_mode)
        {
          case ::build2::build::cli::unknown_mode::skip:
          {
            s.skip ();
            r = true;
            continue;
          }
          case ::build2::build::cli::unknown_mode::stop:
          {
            break;
          }
          case ::build2::build::cli::unknown_mode::fail:
          {
            throw ::build2::build::cli::unknown_argument (o);
          }
        }

        break;
      }

      return r;
    }
  }
}

// Begin epilogue.
//
//
// End epilogue.
