//
// Created by Rostyslav Druzhchenko on 11.10.2020.
//

#ifndef INC_04_USH_MX_CD_H
#define INC_04_USH_MX_CD_H

void mx_cd_parse_arguments(const char *line, char *flag, char **dir);
int mx_cd_validate_input(char flag, const char *dir);
void mx_cd_do(char flag, const char *dir);

const char *mx_get_home_dir();
const char *mx_get_pwd_dir();

char *mx_cd_resolve_path(const char *dir);

#endif //INC_04_USH_MX_CD_H
