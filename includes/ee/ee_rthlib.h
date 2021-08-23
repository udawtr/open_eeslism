#pragma once

// @brief 地下の温度または地表面温度の計算

/*
 * @brief 地中温度の計算
 *
 * @param[IN] Z     地中深さ
 * @param[IN] n     通日
 * @param[IN] nmx   日平均気温の年最高気温が発生する日の通日(地中温度計算用) (VCFILE daymx)
 * @param[IN] Tgro  年平均気温 [℃]
 * @param[IN] DTg   気温年較差 [℃]
 * @param[IN] a     土の熱拡散率 [m2/s]
 *
 * @return 地中温度 [℃]
 */
double Tearth (double Z, int n, int nmx, double Tgro, double DTg, double a);


/*
 * @brief 地下の温度または地表面温度の計算
 *
 * @param[IN]     day    通日
 * @param[IN]     daymx  日平均気温の年最高気温が発生する日の通日(地中温度計算用) (VCFILE daymx)
 * @param[IN]     Tgrav  年平均気温 [℃]
 * @param[IN]     DTgr   気温年較差 [℃]
 * @param[IN,OUT] Exs    外表面方位データ
 * @param[IN]     Wd     気象データ
 * @param[IN]     tt     時
 */
void Exsfter (int day, int daymx, double Tgrav, double DTgr, EXSF *Exs,WDAT *Wd, int tt);
