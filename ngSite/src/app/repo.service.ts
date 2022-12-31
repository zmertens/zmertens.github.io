import { Injectable } from '@angular/core';
import { REPOES } from './mock-repoes';
import { Repo } from './repo';
import { Observable, of } from 'rxjs';

@Injectable({
  providedIn: 'root'
})
export class RepoService {

  constructor() { }

  getRepoes(): Observable<Repo[]> {
    const repoes = of(REPOES)
    return repoes;
  }
}
