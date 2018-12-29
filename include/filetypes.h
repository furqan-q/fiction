//
// Created by marcel on 16.07.18.
//

#ifndef FICTION_FILETYPES_H
#define FICTION_FILETYPES_H

#include "logic_network.h"
#include "verilog_parser.h"
#include "fcn_cell_layout.h"
#include "qca_writer.h"
#include <boost/filesystem/path.hpp>
#include <alice/alice.hpp>

namespace alice
{
    /**
     * Synthesized gate level verilog files.
     */
    ALICE_ADD_FILE_TYPE_READ_ONLY(verilog, "Verilog")
    /**
     * Parses verilog files. Gate level netlists are supported. The lorina verilog parser is used. At the moment only
     * 2-input gates + 3-input MAJ in assign notation are supported. Using ABC, those can be generated by the commands
     *
     * read <file>
     * strash
     * write <file>.v
     *
     * For more information see: https://github.com/marcelwa/lorina
     */
    ALICE_READ_FILE(logic_network_ptr, verilog, filename, cmd)
    {
        auto name = boost::filesystem::path{filename}.stem().string();
        auto ln = std::make_shared<logic_network>(std::move(name));
        lorina::read_verilog(filename, verilog_parser{ln});

        cmd.store<logic_network_ptr>().extend();

        return ln;
    }
    /**
     * QCADesigner files.
     */
    ALICE_ADD_FILE_TYPE_WRITE_ONLY(qca, "QCA")
    /**
     * Writes a fcn_cell_layout to a QCADesigner file.
     *
     * QCADesigner is available at: https://waluslab.ece.ubc.ca/qcadesigner/
     */
    ALICE_WRITE_FILE(fcn_cell_layout_ptr, qca, fcl, filename, cmd)
    {
        (void)cmd; // fix compiler warning
        qca::write(fcl, filename);
    }
}


#endif //FICTION_FILETYPES_H
