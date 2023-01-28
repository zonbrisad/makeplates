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
class TemplateX:
    text: str = ""
    # preamble_text: str = ""
    header_text: str = ""
    includes_text: str = ""
    macros_text: str = ""
    datatypes_text: str = ""
    variables_text: str = ""
    prototypes_text: str = ""
    code_text: str = ""
    main_func_text: str = ""
    main_text: str = ""

#    dependencies: List[TemplateX] = field(default_factory=list)

    def add(self, a: TemplateX):
        # self.preamble_text += a.preamble_text
        self.header_text += a.header_text
        self.includes_text += a.includes_text
        self.variables_text += a.variables_text
        self.code_text += a.code_text
        self.main_func_text += a.main_func_text
        self.main_text += a.main_text


@dataclass
class TConf:
    """Template configuration class"""
    name: str = ""
    author: str = ""
    description: str = ""
    date: str = ""
    email: str = ""
    license: str = ""
    org: str = ""
    project: str = ""

    out_dir: str = ""

    has_preamble: bool = True
    has_header: bool = True
    has_main: bool = False
    has_main_application: bool = False
    has_separators: bool = False
    has_argparse: bool = False
    has_argparse_sub: bool = False
    has_debug: bool = False

    def __init__(self, args: argparse.ArgumentParser) -> None:
        self.args = args
        self.date = datetime.now().strftime("%Y-%m-%d")
        self.out_dir = os.getcwd()
        self.has_main = self.args.main
        self.has_separators = self.args.separators

        self.set_attribute("name", "Enter module name", "")
        self.set_attribute("description", "Enter brief description", "")
        self.set_attribute("author", "Enter name of author", "BP_NAME")
        self.set_attribute("email", "Enter email of author", "BP_EMAIL")

        # if external header, read into var
        if self.args.header is not None:
            self.header = TemplateX()
            with self.args.header as f:
                self.header.header_text = f.read()
        else:
            self.header = t_header

    def set_attribute(self, attribute: str, question: str, env: str):
        if getattr(self.args, attribute) is not None:  # If command line arguments are present use them
            setattr(self, attribute, getattr(self.args, attribute))
        else:
            setattr(self, attribute,
                    Query.read_string(question, os.getenv(env)))


@dataclass
class ClassTemplate():
    name: str = ""
    parrent: str = ""
    methods: str = ""
    dataclass: bool = False
    _init: str = ""
    _str: str = ""
    _eq: str = ""
    vars = None

    def add_var(self, name, type="", default=""):
        if self.vars is None:
            self.vars = []

        self.vars.append({name, type, default})

    def __str__(self) -> str:
        if self.vars is None:
            self.vars = []

        str = ""
        if self.dataclass:
            str = "@dataclass\n"

        if self.parrent == "":
            str += f"class {self.name}:"
        else:
            str = f"class {self.name}({self.parrent}):"

        for v in self.vars:
            str += f"    {v[0]}"

        return str


class Template(TemplateX):
    """docstring for template."""

    def __init__(self, conf: TConf, pre: List[TemplateX], post: List[TemplateX]):
        super().__init__()
        self.conf = conf
        self.pre = pre
        self.post = post

    def clear(self):
        self.text = ""

    def replace(self, old: str, new: str):
        self.text = self.text.replace(old, new)

    def add_separator(self, header):
        if self.conf.has_separators:
            self.text += f"\n// {header} {'-'*(70-len(header))}\n\n\n"
        # else:
        #     self.text += "\n\n"

    def generate(self):
        self.clear()

        # if self.conf.has_preamble:
        #     self.add(t_preamble)

        if self.conf.has_header:
            self.add(self.conf.header)

        for x in self.pre:
            self.add(x)

        # if Query.read_bool("Include logging?", default=True):
        #     self.add(t_logging)

        # if Query.read_bool("Include argparse?", default=True):
        #     if Query.read_bool("Argparse with subcommands?", default=False):
        #         self.add(t_argtable_cmd)
        #     else:
        #         self.add(t_argtable)

        if self.conf.has_main:
            self.add(t_main)

        for x in self.post:
            self.add(x)

        # self.text += self.preamble_text
        self.text += self.header_text
        self.add_separator("Include")
        self.text += self.includes_text
        self.add_separator("Macros")
        self.text += self.macros_text
        self.add_separator("Datatypes")
        self.text += self.datatypes_text
        self.add_separator("Variables")
        self.text += self.variables_text
        self.add_separator("Prototypes")
        self.text += self.prototypes_text
        self.add_separator("Code")
        self.text += self.code_text

        # if self.conf.has_main or self.conf.has_main_application:
        #     self.text += "def main() -> None:\n"
        #     if self.main_func_text == "":
        #         self.text += "    pass"
        #     else:
        #         self.text += self.main_func_text
        #     self.text += "\n\n"
        #     self.text += self.main_text

        self.replace("__NAME__", self.conf.name)
        self.replace("__DESCRIPTION__", self.conf.description)
        self.replace("__AUTHOR__", self.conf.author)

        if self.conf.email == "":
            self.replace("__EMAIL__", "")
        else:
            self.replace("__EMAIL__", f"<{self.conf.email}>")

        self.replace("__DATE__", self.conf.date)
        self.replace("__LICENSE__", self.conf.license)

    def write(self, dir=None) -> str:
        if dir is None:
            file_name = f"{self.conf.out_dir}/{self.conf.name}"
        else:
            file_name = f"{dir}/{self.conf.name}"

        with open(file_name, "w") as file:
            file.write(self.text)
        os.chmod(file_name, 0o770)
        return file_name

    def __str__(self) -> str:
        return self.text


def print_info():
    print("Script name    " + AppName)
    print("Script version " + AppVersion)
    print("Script path    " + os.path.realpath(__file__))



t_header = TemplateX(
    header_text="""\
 *---------------------------------------------------------------------------
 * @brief    __DESCRIPTION__
 *
 * @file     __FILENAME__
 * @author   __AUTHOR__
 * @date     __DATE__
 * @license  __LICENSE__
 *
 *---------------------------------------------------------------------------
 *
 *
 */
""" 
)

t_main = TemplateX(
    main_text="""\
int main(int argc, char *argv[]) {
        
    return 0;
}
"""
)



t_application = TemplateX(
    variables_text="""\
class App:
    NAME = "__NAME__"
    VERSION = "0.01"
    DESCRIPTION = "__DESCRIPTION__"
    LICENSE = ""
    AUTHOR = "__AUTHOR__"
    EMAIL = "__EMAIL__"
    ORG = "__ORGANISATION__"
    HOME = ""
    ICON = ""

"""
)



def create_project(template: Template):

    if Query.read_bool("Do you want to create a project?", False):
        proj = ProjectGenerator()
        proj.project_name = template.conf.name
        proj.query()
        proj.create()
        proj.git_add(template.write(proj.project_dir))
        proj.commit()
        return True

    return False


def cmd_new(args):
    conf = TConf(args)
    conf.has_main = True
    conf.has_main_application = True
    conf.has_separators = True

    template = Template(conf, [], [])
    template.generate()
    print(template)

    # if not create_project(template):
    #     template.write()


def cmd_newa(args):
    conf = TConf(args)
    conf.has_main = False
    conf.has_main_application = True
    conf.has_separators = True

    template = Template(conf, [t_application], [])
    template.generate()

    if not create_project(template):
        template.write()


def cmd_newmod(args):
    conf = TConf(args)
    conf.has_main = True
    conf.has_main_application = False

    template = Template(conf, [], [])
    template.generate()
    template.write()

    
def cmd_newmin(args):
    conf = TConf(args)
    conf.has_main = True
    conf.has_main_application = False

    template = Template(conf, [], [])
    template.generate()
    template.write()


def cmd_newqt(args):
    conf = TConf(args)
    conf.has_main = False
    conf.has_main_application = True
    conf.has_separators = True

    template = Template(conf, [t_application], [t_qt5])
    template.generate()

    if not create_project(template):
        template.write()


def cmd_newgtk(args):
    conf = TConf(args)
    conf.has_main = False
    conf.has_main_application = True
    conf.has_separators = True
    template = Template(conf, [t_application], [t_gtk])
    template.generate()

    if not create_project(template):
        template.write()


def cmd_newp(args):
    proj = ProjectGenerator()
    proj.query()
    proj.create()
    proj.commit()


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
    parrent_parser.add_argument("--name",
                                type=str,
                                help="Name of C module"
                                )
    parrent_parser.add_argument("--description",
                                type=str,
                                help="Brief description"
                                )
    parrent_parser.add_argument("--author",
                                type=str,
                                help="Name of author"
                                )
    parrent_parser.add_argument("--email",
                                type=str,
                                help="Email of author"
                                )
    parrent_parser.add_argument("--project",
                                type=str,
                                help="Name of project"
                                )
    # parrent_parser.add_argument("--license",
    #                             type=str,
    #                             help="License of new file",
    #                             default=conf.license)

    parrent_parser.add_argument("--main",
                                action="store_true",
                                help="Add main function block",
                                default=False)
    parrent_parser.add_argument("--header",
                                type=argparse.FileType("r"),
                                help="Include external header"
                                )
    parrent_parser.add_argument("--dir",
                                type=str,
                                help="Project source directory",
                                default=".")
    parrent_parser.add_argument("--basedir",
                                type=str,
                                help="Project directory",
                                default=".")
    parrent_parser.add_argument("--write",
                                action="store_true",
                                help="Write file to disk",
                                default=False)
    parrent_parser.add_argument("--printheader",
                                action="store_true",
                                help="Print default header to stdout",
                                default=False)
    parrent_parser.add_argument("--separators",
                                action="store_true",
                                help="Add code separators",
                                default=False)
#    parrent_parser.add_argument("--outfile",
#                                type=argparse.FileType("w",0),
#                                help="Write template to file")
    parrent_parser.add_argument("--debug",
                                action="store_true",
                                help="Print debug information")
    parrent_parser.add_argument("--version",
                                action="version",
                                help="Print application version",
                                version=AppVersion)
    parrent_parser.add_argument("--no_interaction",
                                action="store_true",
                                help="Disable interactive questions")

    # options parsing
    parser = argparse.ArgumentParser(
            prog=AppName,
            description="C template generator",
            epilog="Makeplates <https://github.com/zonbrisad/makeplates.git>",
            parents=[parrent_parser],
        )

    subparsers = parser.add_subparsers(title="Commands",
                                       help="",
                                       description="")
                                       
    parser_new = subparsers.add_parser("new", parents=[parrent_parser],
                                       help="Create a new c file")
    parser_new.set_defaults(func=cmd_new)

    parser_new = subparsers.add_parser("newm", parents=[parrent_parser],
                                       help="Create a new python module")
    parser_new.set_defaults(func=cmd_newmod)
    parser_new = subparsers.add_parser("newmin", parents=[parrent_parser],
                                       help="Create a new minimal python file")
    parser_new.set_defaults(func=cmd_newmin)
    parser_new = subparsers.add_parser("newa", parents=[parrent_parser],
                                       help="Create a new application")
    parser_new.set_defaults(func=cmd_newa)
    parser_new = subparsers.add_parser("newqt", parents=[parrent_parser],
                                       help="Create a new QT5 application")
    parser_new.set_defaults(func=cmd_newqt)
    parser_new = subparsers.add_parser("newgtk", parents=[parrent_parser],
                                       help="Create a new GTK3+ application")
    parser_new.set_defaults(func=cmd_newgtk)
    parser_new = subparsers.add_parser("newp", parents=[parrent_parser],
                                       help="Create python project")
    parser_new.set_defaults(func=cmd_newp)

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
    except SystemExit as e:        # sys.exit()
        raise e
    except Exception as e:
        print('ERROR, UNEXPECTED EXCEPTION')
        print(str(e))
        traceback.print_exc()
        os._exit(1)
