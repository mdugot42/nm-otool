#include "nm.h"

int is_macho_32(t_bin *bin)
{
	struct mach_header *header;
	t_list *cmds;
	t_list *sections;
	t_list *syms;

	if (check_magic_number(bin, MH_MAGIC))
	{
		if (!dump_data(&header, bin, DESCRIPTION(MACH_HEADER_D)))
			return 0;
//		ft_printf("ft_nm: %s: 32 bits mach-o.\n", bin->filename);
		cmds = save_commands(bin, header->sizeofcmds);
		if (!cmds)
			return 0;
		sections = save_usections(cmds);
		syms = save_all_symbol(cmds, 32, bin);
		if (!ft_strcmp(NM, TARGET))
			display_all(syms, sections, 32);
		if (!ft_strcmp(OTOOL, TARGET))
			otool(sections, bin);
		ft_lstfree(&cmds);
		ft_lstfree(&sections);
		ft_lstfree(&syms);
		return 1;
	}
	return 0;
}

int is_macho_64(t_bin *bin)
{
	struct mach_header_64 *header;
	t_list *cmds;
	t_list *sections;
	t_list *syms;

	if (check_magic_number(bin, MH_MAGIC_64))
	{
		if (!dump_data(&header, bin, DESCRIPTION(MACH_HEADER_64_D)))
			return 0;
		bin->cputype = header->cputype;
		bin->cpusubtype = header->cpusubtype;
//		ft_printf("ft_nm: %s: 64 bits mach-o.\n", bin->filename);
		cmds = save_commands(bin, header->sizeofcmds);
		if (!cmds)
			return 0;
		sections = save_usections(cmds);
		syms = save_all_symbol(cmds, 64, bin);
		if (!ft_strcmp(NM, TARGET))
			display_all(syms, sections, 64);
		if (!ft_strcmp(OTOOL, TARGET))
			otool(sections, bin);
		ft_lstfree(&cmds);
		ft_lstfree(&sections);
		ft_lstfree(&syms);
		return 1;
	}
	return 0;
}
