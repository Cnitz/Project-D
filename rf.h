/*
 * Retruns a resampled table, in which the rows from src are randomly copied the 
 * new table. It should have the same number of rows as src. 
 * It is okay for rows to be copied more than once into the new table.
 */
Table* resample(Table* src);