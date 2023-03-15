#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# --------------------------------------------------------------------------
#
# C template generator
#
# File:    mptemplate.py
# Author:  Peter Malmberg <peter.malmberg@gmail.com>
# Date:    2016-02-19
# Version: 0.3
# Python:  >=3
# License: MIT
#
# ---------------------------------------------------------------------------

# History -------------------------------------------------------------------
# - Ver 0.3
# Major rewrite for better code generation
#

# Todo ----------------------------------------------------------------------
#

# Imports -------------------------------------------------------------------

from __future__ import annotations

import argparse
import json
import os
import sys
import traceback
from dataclasses import dataclass
from datetime import datetime
from typing import List

from bashplates import Bp
from query import Query
from Project import ProjectGenerator

from templatec import *

# Settings ------------------------------------------------------------------

AppName = "mptemplate"
AppVersion = "0.3"
AppLicense = "MIT"
AppAuthor = "Peter Malmberg <peter.malmberg@gmail.com>"

# Absolute path to script itself
self_dir = os.path.abspath(os.path.dirname(sys.argv[0]))


class App:
    NAME = "mpterm"
    VERSION = "0.2"
    DESCRIPTION = "MpTerm is a simple serial terminal program"
    LICENSE = ""
    AUTHOR = "Peter Malmberg"
    EMAIL = "peter.malmberg@gmail.com"
    ORG = ""
    HOME = "github.com/zonbrisad/mpterm"
    ICON = f"{self_dir}/icons/mp_icon2.png"


template_dir = f"{self_dir}/pyplate"
# readme_md = f"{template_dir}/README.md"

# Code ----------------------------------------------------------------------


@dataclass
class TConf:
    """TGenerator configuration class"""

    name: str = ""
    author: str = ""
    description: str = ""
    date: str = ""
    email: str = ""
    license: str = ""
    org: str = ""
    project: str = ""

    out_dir: str = ""

    has_header: bool = True
    #has_main: bool = False
    #has_main_application: bool = False
    has_separators: bool = False
    has_argparse: bool = False
    has_argparse_sub: bool = False
    has_debug: bool = False

    filename_h: str = ""
    filename_c: str = ""

    def __init__(self, args: argparse.ArgumentParser, list) -> None:
        self.args = args
        self.date = datetime.now().strftime("%Y-%m-%d")
        self.out_dir = os.getcwd()
        self.has_main = self.args.main
        self.has_separators = self.args.separators
        self.header = t_header
        self.list = list

    def query(self) -> None:
        self.set_attribute("name", "Enter module name", "")
        self.set_attribute("description", "Enter brief description", "")
        self.set_attribute("author", "Enter name of author", "BP_NAME")
        self.set_attribute("email", "Enter email of author", "BP_EMAIL")

        self.filename_c = f"{self.name}.c"
        self.filename_h = f"{self.name}.h"

        for l in self.list:
            l.incl = Query.read_bool(l.query_text, l.incl)
            #print(l.query_text)
            
        # if external header, read into var
        if self.args.header is not None:
            self.header = TemplateC()
            with self.args.header as f:
                self.header.header_text = f.read()

    def set_attribute(self, attribute: str, question: str, env: str):
        if (
            getattr(self.args, attribute) is not None
        ):  # If command line arguments are present use them
            setattr(self, attribute, getattr(self.args, attribute))
        else:
            setattr(self, attribute, Query.read_string(question, os.getenv(env)))


class TGenerator:
    """docstring for template."""

    # text: str = ""

    def __init__(
        self, conf: TConf, main: TemplateC, pre: List[TemplateC], post: List[TemplateC]
    ):
        # super().__init__()
        self.templ = TemplateC()
        self.conf = conf
        self.pre = pre
        self.post = post
        self.main = main
        if self.conf.has_header:
            self.add(self.conf.header)

        for x in self.pre:
            self.add(x)

        if self.conf.has_main:
            self.add(t_main)

        for x in self.post:
            self.add(x)

    def add(self, t: TemplateC) -> None:
        self.templ.add(t)
        pass

    def clear(self):
        self.text = ""

    def replace(self, old: str, new: str):
        self.text = self.text.replace(old, new)

    def add_separator(self, header):
        if self.conf.has_separators:
            self.text += f"\n// {header} {'-'*(73-len(header))}\n\n"
        # else:
        #     self.text += "\n\n"

    def replace_keys(self, filename: str):
        self.replace("__NAME__", self.conf.name)
        self.replace("__DESCRIPTION__", self.conf.description)
        self.replace("__AUTHOR__", self.conf.author)

        if self.conf.email == "":
            self.replace("__EMAIL__", "")
        else:
            self.replace("__EMAIL__", f"<{self.conf.email}>")

        self.replace("__DATE__", self.conf.date)
        self.replace("__LICENSE__", self.conf.license)

        self.replace("__FILENAME__", filename)

    def generate_h(self):
        self.clear()

        self.text += self.templ.header_text

        self.text += self.templ.h_pre_text

        self.add_separator("Include")
        self.text += self.templ.h_includes_text

        self.add_separator("Macros")
        self.text += self.templ.h_macros_text

        self.add_separator("Datatypes")
        self.text += self.templ.h_datatypes_text

        self.add_separator("Variables")
        self.text += self.templ.h_variables_text

        self.add_separator("Prototypes")
        self.text += self.templ.h_prototypes_text

        self.text += self.templ.h_post_text

        self.replace_keys(self.conf.filename_h)

    def generate_c(self):
        self.clear()

        self.text += self.templ.header_text

        # self.text += self.c_pre_text

        self.add_separator("Include")
        self.text += self.templ.c_includes_text
        self.text += f"#include \"{self.conf.filename_h}\""

        self.add_separator("Macros")
        self.text += self.templ.c_macros_text

        self.add_separator("Datatypes")
        self.text += self.templ.c_datatypes_text

        self.add_separator("Variables")
        self.text += self.templ.c_variables_text

        self.add_separator("Prototypes")
        self.text += self.templ.c_prototypes_text

        self.add_separator("Code")
        self.text += self.templ.c_code_text

        if self.main != None:
            self.text += self.main.main_begin_text

        if self.conf.has_main or self.conf.has_main_application:

            self.text += self.templ.main_begin_text
            self.text += self.templ.main_vars_text
            self.text += self.templ.main_func_text
            self.text += self.templ.main_end_text

        if self.main != None:
            self.text += self.main.main_end_text

        # self.text += self.c_post_text

        self.replace_keys(self.conf.filename_c)

    def generate(self):
        self.generate_h()
        self.file_h = self.text
        self.generate_c()
        self.file_c = self.text

    def write(self, dir=None) -> str:
        self._write(self.file_h, self.conf.filename_h, None)
        self._write(self.file_c, self.conf.filename_c, None)

    def _write(self, data, filename: str, dir=None) -> str:
        if dir is None:
            out_file = f"{self.conf.out_dir}/{filename}"
        else:
            out_file = f"{dir}/{filename}"

        with open(out_file, "w") as file:
            file.write(data)
        os.chmod(out_file, 0o770)
        return out_file

    def __str__(self) -> str:
        return self.file_h + self.file_c


def print_info():
    print("Script name    " + AppName)
    print("Script version " + AppVersion)
    print("Script path    " + os.path.realpath(__file__))


def create_project(template: TGenerator):

    if Query.read_bool("Do you want to create a project?", False):
        proj = ProjectGenerator()
        proj.project_name = template.conf.name
        proj.query()
        proj.create()
        proj.git_add(template.write(proj.project_dir))
        proj.commit()
        return True

    return False


def generate(conf: TConf, main: TemplateC, pre: List(TemplateC), post: List(TemplateC)):
    template = TGenerator(conf, main, pre, post)
    template.generate()
    #print(template)
    template.write()

def cmd_new(args):
    conf = TConf(args, [])

    conf.name = "testfil"
    conf.author = "Peter Malmberg"
    conf.has_header = True
    #conf.has_main = True
    conf.description = "A test case"

    #conf.has_main = True
    conf.has_main_application = True
    conf.has_separators = True

   
    # template = TGenerator(conf, t_main, [t_sentinel, t_cplusplus], [])
    # template.generate()
    generate(conf, t_main, [t_app_info], [])

    # if not create_project(template):
    #     template.write()


def cmd_newa(args):
    conf = TConf(args, [])
    conf.has_main = False
    conf.has_main_application = True
    conf.has_separators = True
    conf.query()
    # template = TGenerator(conf, t_main, [t_app_info, t_argtable], [])
    # template.generate()
    generate(conf, t_main, [t_app_info, t_argtable], [])

#    if not create_project(template):
#        template.write()


def cmd_newavr(args):
    conf = TConf(args, [])
    conf.has_main = False
    conf.has_main_application = True
    conf.has_separators = True
    conf.query()
    #template = TGenerator(conf, t_main, [t_app_info, t_avr], [])
    #template.generate()
    generate(conf, t_main,  [t_app_info, t_avr], [])

#    if not create_project(template):
#        template.write()


def cmd_newmod(args):
    conf = TConf(args,[t_sentinel, t_cplusplus])
    conf.has_main = False
    conf.has_main_application = False
    conf.has_separators = True
    conf.query()
    template = TGenerator(conf, None, [], [])
    template.generate()


# def cmd_newmin(args):
#     conf = TConf(args)
#     conf.has_main = True
#     conf.has_main_application = False

#     template = TGenerator(conf, [], [])
#     template.generate()
#     template.write()


# def cmd_newqt(args):
#     conf = TConf(args)
#     conf.has_main = False
#     conf.has_main_application = True
#     conf.has_separators = True

#     template = TGenerator(conf, [t_app_info], [t_qt5])
#     template.generate()

#     if not create_project(template):
#         template.write()


# def cmd_newgtk(args):
#     conf = TConf(args)
#     conf.has_main = False
#     conf.has_main_application = True
#     conf.has_separators = True
#     template = TGenerator(conf, [t_app_info], [t_gtk])
#     template.generate()

#     if not create_project(template):
#         template.write()


# def cmd_newp(args):
#     proj = ProjectGenerator()
#     proj.query()
#     proj.create()
#     proj.commit()


class Settings:
    SETTINGS_DIR = "~/.config/pyplate"
    SETTINGS_FILE = "pyplate.json"

    def __init__(self) -> None:
        with open("pyplate/pyplate.json") as f:
            data = json.load(f)

        print(data)

    def create(self) -> None:
        # Create personal settings
        pass


def main() -> None:

    # logging.basicConfig(level=logging.DEBUG,
    #                     format="[%(levelname)s]%(asctime)s %(message)s")

    parrent_parser = argparse.ArgumentParser(add_help=False)
    parrent_parser.add_argument("--name", type=str, help="Name of C module")
    parrent_parser.add_argument("--description", type=str, help="Brief description")
    parrent_parser.add_argument("--author", type=str, help="Name of author")
    parrent_parser.add_argument("--email", type=str, help="Email of author")
    parrent_parser.add_argument("--project", type=str, help="Name of project")
    # parrent_parser.add_argument("--license",
    #                             type=str,
    #                             help="License of new file",
    #                             default=conf.license)

    parrent_parser.add_argument(
        "--main", action="store_true", help="Add main function block", default=False
    )
    parrent_parser.add_argument(
        "--header", type=argparse.FileType("r"), help="Include external header"
    )
    parrent_parser.add_argument(
        "--dir", type=str, help="Project source directory", default="."
    )
    parrent_parser.add_argument(
        "--basedir", type=str, help="Project directory", default="."
    )
    parrent_parser.add_argument(
        "--write", action="store_true", help="Write file to disk", default=False
    )
    parrent_parser.add_argument(
        "--printheader",
        action="store_true",
        help="Print default header to stdout",
        default=False,
    )
    parrent_parser.add_argument(
        "--separators", action="store_true", help="Add code separators", default=False
    )
    #    parrent_parser.add_argument("--outfile",
    #                                type=argparse.FileType("w",0),
    #                                help="Write template to file")
    parrent_parser.add_argument(
        "--debug", action="store_true", help="Print debug information"
    )
    parrent_parser.add_argument(
        "--version",
        action="version",
        help="Print application version",
        version=AppVersion,
    )
    parrent_parser.add_argument(
        "--no_interaction", action="store_true", help="Disable interactive questions"
    )

    # options parsing
    parser = argparse.ArgumentParser(
        prog=AppName,
        description="C/C++ template generator",
        epilog="Part of Makeplates <https://github.com/zonbrisad/makeplates.git>",
        parents=[parrent_parser],
    )

    subparsers = parser.add_subparsers(title="Commands", help="", description="")

    parser_new = subparsers.add_parser(
        "new", 
        parents=[parrent_parser], 
        help="Create a new C file"
    )
    parser_new.set_defaults(func=cmd_new)

    parser_new = subparsers.add_parser(
        "newavr", parents=[parrent_parser], help="Create a new AVR application"
    )
    parser_new.set_defaults(func=cmd_newavr)
    
    parser_new = subparsers.add_parser(
        "newm", parents=[parrent_parser], help="Create new C module"
    )
    parser_new.set_defaults(func=cmd_newmod)
    
    parser_new = subparsers.add_parser(
        "newa", parents=[parrent_parser], help="Create a new C application"
    )
    parser_new.set_defaults(func=cmd_newa)

    # parser_new = subparsers.add_parser(
    #     "newqt", parents=[parrent_parser], help="Create a new QT5 application"
    # )
    # parser_new.set_defaults(func=cmd_newqt)
    # parser_new = subparsers.add_parser(
    #     "newgtk", parents=[parrent_parser], help="Create a new GTK3+ application"
    # )
    # parser_new.set_defaults(func=cmd_newgtk)
    

    args = parser.parse_args()

    if hasattr(args, "func"):
        args.func(args)
        exit(0)

    if args.printheader:
        print(t_header.header_text)
        exit(0)

    parser.print_help()


if __name__ == "__main__":
    try:
        main()
        sys.exit(0)
    except KeyboardInterrupt as e:  # Ctrl-C
        raise e
    except SystemExit as e:  # sys.exit()
        raise e
    except Exception as e:
        print("ERROR, UNEXPECTED EXCEPTION")
        print(str(e))
        traceback.print_exc()
        os._exit(1)
