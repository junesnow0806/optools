/*main data structure */
class problem
{
private:
    double objoffset;                        /**< objective offset from bound shifting and fixing (fixed vars result) */
    double objscale;                         /**< scalar applied to objective function; external objective value is
                                              *   extobj = objsense * objscale * (intobj + objoffset) */
    double objlim;                           /**< objective limit as external value (original problem space) */
    double dualbound;                        /**< dual bound as external value (original problem space) which is given or update during presolving */
    char *name;                              /**< problem name */
    SCIP_DECL_PROBCOPY((*probcopy));         /**< copies user data if you want to copy it to a subscip, or NULL */
    SCIP_DECL_PROBDELORIG((*probdelorig));   /**< frees user data of original problem */
    SCIP_DECL_PROBTRANS((*probtrans));       /**< creates user data of transformed problem by transforming original user data */
    SCIP_DECL_PROBDELTRANS((*probdeltrans)); /**< frees user data of transformed problem */
    SCIP_DECL_PROBINITSOL((*probinitsol));   /**< solving process initialization method of transformed data */
    SCIP_DECL_PROBEXITSOL((*probexitsol));   /**< solving process deinitialization method of transformed data */
    SCIP_PROBDATA *probdata;                 /**< user problem data set by the reader */
    SCIP_HASHTABLE *varnames;                /**< hash table storing variable's names */
    SCIP_VAR **vars;                         /**< array with active variables ordered binary, integer, implicit, continuous */
    SCIP_VAR **fixedvars;                    /**< array with fixed and aggregated variables */
    SCIP_VAR **deletedvars;                  /**< array to temporarily store deleted variables */
    SCIP_HASHTABLE *consnames;               /**< hash table storing constraints' names */
    SCIP_CONS **conss;                       /**< array with constraints of the problem */
    int varssize;                            /**< available slots in vars array */
    int nvars;                               /**< number of active variables in the problem (used slots in vars array) */
    int nbinvars;                            /**< number of binary variables */
    int nintvars;                            /**< number of general integer variables */
    int nimplvars;                           /**< number of implicit integer variables */
    int ncontvars;                           /**< number of continuous variables */
    int ncolvars;                            /**< number of variables with attached column information */
    int fixedvarssize;                       /**< available slots in fixedvars array */
    int nfixedvars;                          /**< number of fixed and aggregated variables in the problem */
    int deletedvarssize;                     /**< available slots in deletedvars array */
    int ndeletedvars;                        /**< number of deleted variables in the problem */
    int nobjvars;                            /**< number of variables with a non-zero objective coefficient */
    int consssize;                           /**< available slots in conss array */
    int nconss;                              /**< number of constraints in the problem (number of used slots in conss array) */
    int maxnconss;                           /**< maximum number of constraints existing at the same time */
    int startnvars;                          /**< number of variables existing when problem solving started */
    int startnconss;                         /**< number of constraints existing when problem solving started */
                                             /*SCIP_OBJSENSE objsense;                  /**< objective sense of the original problem */
    bool objisintegral;                      /**< is objective value always integral for feasible solutions? */
    bool transformed;                        /**< TRUE iff problem is the transformed problem */
    bool nlpenabled;                         /**< marks whether an NLP relaxation should be constructed */
    bool permuted;                           /**< TRUE iff the problem is already permuted */
    bool conscompression;                    /**< TRUE for problems for which constraint compression on a set of fixed variables is desired */
};