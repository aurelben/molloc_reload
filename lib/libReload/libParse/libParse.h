#ifndef LIBPARSE_H__
# define LIBPARSE_H__
void add_option(sll_s *p_sll, void *option, int is_required, void *data);
void **validate_options(char **option, sll_s *optionList);
void *check_option(char *option, sll_s *optionList);
int is_required(char **option, sll_ *optionList);


#endif /* !LIBPARSE_H__ */
